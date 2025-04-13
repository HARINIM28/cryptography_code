document.addEventListener('DOMContentLoaded', () => {
    const plaintext = document.getElementById('plaintext');
    const keyInput = document.getElementById('key');
    const keySection = document.getElementById('keySection');
    const keyDescription = document.getElementById('keyDescription');
    const outputText = document.getElementById('outputText');
    const encryptBtn = document.getElementById('encryptBtn');
    const decryptBtn = document.getElementById('decryptBtn');
    const copyBtn = document.getElementById('copyBtn');
    const cipherButtons = document.querySelectorAll('.cipher-btn');

    let currentCipher = null;

    // Helper functions
    function mod(n, m) {
        return ((n % m) + m) % m;
    }

    function isCoprime(a, b) {
        const gcd = (x, y) => (!y ? x : gcd(y, x % y));
        return gcd(a, b) === 1;
    }

    function modInverse(a, m) {
        for(let x = 1; x < m; x++) {
            if(((a % m) * (x % m)) % m === 1) return x;
        }
        return 1;
    }

    function createMatrix(text, cols) {
        const matrix = [];
        let row = [];
        for(let i = 0; i < text.length; i++) {
            row.push(text[i]);
            if(row.length === cols || i === text.length - 1) {
                matrix.push(row);
                row = [];
            }
        }
        // Pad last row if necessary
        while(matrix[matrix.length - 1].length < cols) {
            matrix[matrix.length - 1].push('X');
        }
        return matrix;
    }

    // Cipher implementations
    const ciphers = {
        caesar: {
            encrypt: (text, key) => {
                const shift = parseInt(key);
                return text.replace(/[a-zA-Z]/g, char => {
                    const code = char.charCodeAt(0);
                    const isUpper = code >= 65 && code <= 90;
                    const base = isUpper ? 65 : 97;
                    return String.fromCharCode((code - base + shift) % 26 + base);
                });
            },
            decrypt: (text, key) => {
                const shift = parseInt(key);
                return text.replace(/[a-zA-Z]/g, char => {
                    const code = char.charCodeAt(0);
                    const isUpper = code >= 65 && code <= 90;
                    const base = isUpper ? 65 : 97;
                    return String.fromCharCode(mod(code - base - shift, 26) + base);
                });
            }
        },

        atbash: {
            encrypt: (text) => {
                return text.replace(/[a-zA-Z]/g, char => {
                    const code = char.charCodeAt(0);
                    const isUpper = code >= 65 && code <= 90;
                    const base = isUpper ? 65 : 97;
                    return String.fromCharCode(base + (25 - (code - base)));
                });
            },
            decrypt: function(text) { return this.encrypt(text); }
        },

        august: {
            encrypt: (text) => {
                return text.replace(/[a-zA-Z]/g, char => {
                    const code = char.charCodeAt(0);
                    const isUpper = code >= 65 && code <= 90;
                    const base = isUpper ? 65 : 97;
                    return String.fromCharCode((code - base + 1) % 26 + base);
                });
            },
            decrypt: (text) => {
                return text.replace(/[a-zA-Z]/g, char => {
                    const code = char.charCodeAt(0);
                    const isUpper = code >= 65 && code <= 90;
                    const base = isUpper ? 65 : 97;
                    return String.fromCharCode(mod(code - base - 1, 26) + base);
                });
            }
        },

        affine: {
            encrypt: (text, key) => {
                const [a, b] = key.split(',').map(Number);
                return text.replace(/[a-zA-Z]/g, char => {
                    const code = char.charCodeAt(0);
                    const isUpper = code >= 65 && code <= 90;
                    const base = isUpper ? 65 : 97;
                    return String.fromCharCode(mod(a * (code - base) + b, 26) + base);
                });
            },
            decrypt: (text, key) => {
                const [a, b] = key.split(',').map(Number);
                const aInverse = modInverse(a, 26);
                return text.replace(/[a-zA-Z]/g, char => {
                    const code = char.charCodeAt(0);
                    const isUpper = code >= 65 && code <= 90;
                    const base = isUpper ? 65 : 97;
                    return String.fromCharCode(mod(aInverse * (code - base - b), 26) + base);
                });
            }
        },

        vigenere: {
            encrypt: (text, key) => {
                let result = '';
                let keyIndex = 0;
                
                for(let i = 0; i < text.length; i++) {
                    const char = text[i];
                    if(/[a-zA-Z]/.test(char)) {
                        const isUpper = char === char.toUpperCase();
                        const plainChar = char.toLowerCase();
                        const keyChar = key[keyIndex % key.length].toLowerCase();
                        const shift = keyChar.charCodeAt(0) - 97;
                        
                        let encryptedChar = String.fromCharCode(mod(plainChar.charCodeAt(0) - 97 + shift, 26) + 97);
                        result += isUpper ? encryptedChar.toUpperCase() : encryptedChar;
                        keyIndex++;
                    } else {
                        result += char;
                    }
                }
                return result;
            },
            decrypt: (text, key) => {
                let result = '';
                let keyIndex = 0;
                
                for(let i = 0; i < text.length; i++) {
                    const char = text[i];
                    if(/[a-zA-Z]/.test(char)) {
                        const isUpper = char === char.toUpperCase();
                        const cipherChar = char.toLowerCase();
                        const keyChar = key[keyIndex % key.length].toLowerCase();
                        const shift = keyChar.charCodeAt(0) - 97;
                        
                        let decryptedChar = String.fromCharCode(mod(cipherChar.charCodeAt(0) - 97 - shift, 26) + 97);
                        result += isUpper ? decryptedChar.toUpperCase() : decryptedChar;
                        keyIndex++;
                    } else {
                        result += char;
                    }
                }
                return result;
            }
        },

        gronsfeld: {
            encrypt: (text, key) => {
                const keyDigits = key.split('').map(Number);
                let result = '';
                let keyIndex = 0;
                
                for(let i = 0; i < text.length; i++) {
                    const char = text[i];
                    if(/[a-zA-Z]/.test(char)) {
                        const isUpper = char === char.toUpperCase();
                        const base = isUpper ? 65 : 97;
                        const shift = keyDigits[keyIndex % keyDigits.length];
                        const newChar = String.fromCharCode(mod(char.charCodeAt(0) - base + shift, 26) + base);
                        result += newChar;
                        keyIndex++;
                    } else {
                        result += char;
                    }
                }
                return result;
            },
            decrypt: (text, key) => {
                const keyDigits = key.split('').map(Number);
                let result = '';
                let keyIndex = 0;
                
                for(let i = 0; i < text.length; i++) {
                    const char = text[i];
                    if(/[a-zA-Z]/.test(char)) {
                        const isUpper = char === char.toUpperCase();
                        const base = isUpper ? 65 : 97;
                        const shift = keyDigits[keyIndex % keyDigits.length];
                        const newChar = String.fromCharCode(mod(char.charCodeAt(0) - base - shift, 26) + base);
                        result += newChar;
                        keyIndex++;
                    } else {
                        result += char;
                    }
                }
                return result;
            }
        },

        beaufort: {
            encrypt: (text, key) => {
                let result = '';
                let keyIndex = 0;
                
                for(let i = 0; i < text.length; i++) {
                    const char = text[i];
                    if(/[a-zA-Z]/.test(char)) {
                        const isUpper = char === char.toUpperCase();
                        const plainChar = char.toLowerCase().charCodeAt(0) - 97;
                        const keyChar = key[keyIndex % key.length].toLowerCase().charCodeAt(0) - 97;
                        const newChar = String.fromCharCode(mod(keyChar - plainChar, 26) + 97);
                        result += isUpper ? newChar.toUpperCase() : newChar;
                        keyIndex++;
                    } else {
                        result += char;
                    }
                }
                return result;
            },
            decrypt: function(text, key) { return this.encrypt(text, key); }
        },

        autoclave: {
            encrypt: (text, key) => {
                const fullKey = key + text;
                return ciphers.vigenere.encrypt(text, fullKey);
            },
            decrypt: (text, key) => {
                let result = '';
                let fullKey = key;
                
                for(let i = 0; i < text.length; i++) {
                    const char = text[i];
                    if(/[a-zA-Z]/.test(char)) {
                        const decrypted = ciphers.vigenere.decrypt(char, fullKey[i]);
                        result += decrypted;
                        fullKey += decrypted;
                    } else {
                        result += char;
                    }
                }
                return result;
            }
        },

        runningkey: {
            encrypt: (text, key) => {
                return ciphers.vigenere.encrypt(text, key);
            },
            decrypt: (text, key) => {
                return ciphers.vigenere.decrypt(text, key);
            }
        },

        hill: {
            encrypt: (text, key) => {
                const matrix = key.split(',').map(Number);
                if(matrix.length !== 4) return "Invalid key matrix";
                
                // Pad text if necessary
                while(text.length % 2 !== 0) text += 'X';
                
                let result = '';
                for(let i = 0; i < text.length; i += 2) {
                    const p1 = text[i].toUpperCase().charCodeAt(0) - 65;
                    const p2 = text[i+1].toUpperCase().charCodeAt(0) - 65;
                    
                    const c1 = mod(matrix[0] * p1 + matrix[1] * p2, 26);
                    const c2 = mod(matrix[2] * p1 + matrix[3] * p2, 26);
                    
                    result += String.fromCharCode(c1 + 65);
                    result += String.fromCharCode(c2 + 65);
                }
                return result;
            },
            decrypt: (text, key) => {
                const matrix = key.split(',').map(Number);
                if(matrix.length !== 4) return "Invalid key matrix";
                
                const det = mod(matrix[0] * matrix[3] - matrix[1] * matrix[2], 26);
                const detInv = modInverse(det, 26);
                
                const adjugate = [
                    matrix[3],
                    -matrix[1],
                    -matrix[2],
                    matrix[0]
                ].map(x => mod(x * detInv, 26));
                
                let result = '';
                for(let i = 0; i < text.length; i += 2) {
                    const c1 = text[i].toUpperCase().charCodeAt(0) - 65;
                    const c2 = text[i+1].toUpperCase().charCodeAt(0) - 65;
                    
                    const p1 = mod(adjugate[0] * c1 + adjugate[1] * c2, 26);
                    const p2 = mod(adjugate[2] * c1 + adjugate[3] * c2, 26);
                    
                    result += String.fromCharCode(p1 + 65);
                    result += String.fromCharCode(p2 + 65);
                }
                return result;
            }
        },

        railfence: {
            encrypt: (text, key) => {
                const rails = parseInt(key);
                const fence = Array(rails).fill('').map(() => []);
                let rail = 0;
                let direction = 1;
                
                for(let i = 0; i < text.length; i++) {
                    fence[rail].push(text[i]);
                    rail += direction;
                    
                    if(rail === rails - 1 || rail === 0) {
                        direction = -direction;
                    }
                }
                
                return fence.flat().join('');
            },
            decrypt: (text, key) => {
                const rails = parseInt(key);
                const fence = Array(rails).fill('').map(() => []);
                let rail = 0;
                let direction = 1;
                
                // Mark positions
                for(let i = 0; i < text.length; i++) {
                    fence[rail].push(i);
                    rail += direction;
                    
                    if(rail === rails - 1 || rail === 0) {
                        direction = -direction;
                    }
                }
                
                // Fill in the text
                let pos = 0;
                const result = new Array(text.length);
                for(let i = 0; i < rails; i++) {
                    for(let j = 0; j < fence[i].length; j++) {
                        result[fence[i][j]] = text[pos++];
                    }
                }
                
                return result.join('');
            }
        },

        route: {
            encrypt: (text, key) => {
                const cols = parseInt(key);
                const matrix = createMatrix(text, cols);
                let result = '';
                
                // Read in spiral order
                while(matrix.length > 0) {
                    // Read right
                    result += matrix[0].join('');
                    matrix.shift();
                    
                    if(matrix.length === 0) break;
                    
                    // Read down
                    for(let i = 0; i < matrix.length; i++) {
                        result += matrix[i].pop();
                    }
                    
                    if(matrix[0].length === 0) break;
                    
                    // Read left
                    result += matrix[matrix.length - 1].reverse().join('');
                    matrix.pop();
                    
                    if(matrix.length === 0) break;
                    
                    // Read up
                    for(let i = matrix.length - 1; i >= 0; i--) {
                        result += matrix[i].shift();
                    }
                }
                
                return result;
            },
            decrypt: (text, key) => {
                const cols = parseInt(key);
                const rows = Math.ceil(text.length / cols);
                const matrix = Array(rows).fill('').map(() => Array(cols).fill(''));
                let index = 0;
                
                // Fill in spiral order
                let top = 0, bottom = rows - 1, left = 0, right = cols - 1;
                
                while(index < text.length) {
                    // Fill right
                    for(let i = left; i <= right && index < text.length; i++) {
                        matrix[top][i] = text[index++];
                    }
                    top++;
                    
                    // Fill down
                    for(let i = top; i <= bottom && index < text.length; i++) {
                        matrix[i][right] = text[index++];
                    }
                    right--;
                    
                    // Fill left
                    for(let i = right; i >= left && index < text.length; i--) {
                        matrix[bottom][i] = text[index++];
                    }
                    bottom--;
                    
                    // Fill up
                    for(let i = bottom; i >= top && index < text.length; i--) {
                        matrix[i][left] = text[index++];
                    }
                    left++;
                }
                
                return matrix.flat().join('');
            }
        },

        myszkowski: {
            encrypt: (text, key) => {
                const keyArray = key.split('');
                const uniqueChars = [...new Set(keyArray)].sort();
                const numCols = key.length;
                const numRows = Math.ceil(text.length / numCols);
                const matrix = Array(numRows).fill('').map(() => Array(numCols).fill(''));
                
                // Fill matrix
                let pos = 0;
                for(let i = 0; i < numRows && pos < text.length; i++) {
                    for(let j = 0; j < numCols && pos < text.length; j++) {
                        matrix[i][j] = text[pos++];
                    }
                }
                
                // Read off by key order
                let result = '';
                uniqueChars.forEach(char => {
                    const indices = keyArray.map((k, i) => k === char ? i : -1).filter(i => i !== -1);
                    for(let row = 0; row < numRows; row++) {
                        indices.forEach(col => {
                            if(matrix[row][col]) result += matrix[row][col];
                        });
                    }
                });
                
                return result;
            },
            decrypt: (text, key) => {
                const keyArray = key.split('');
                const uniqueChars = [...new Set(keyArray)].sort();
                const numCols = key.length;
                const numRows = Math.ceil(text.length / numCols);
                const matrix = Array(numRows).fill('').map(() => Array(numCols).fill(''));
                
                // Calculate positions
                let pos = 0;
                uniqueChars.forEach(char => {
                    const indices = keyArray.map((k, i) => k === char ? i : -1).filter(i => i !== -1);
                    for(let row = 0; row < numRows; row++) {
                        indices.forEach(col => {
                            if(pos < text.length) matrix[row][col] = text[pos++];
                        });
                    }
                });
                
                // Read off row by row
                return matrix.map(row => row.join('')).join('');
            }
        }
    };

    // Cipher requirements and descriptions
    const cipherInfo = {
        caesar: {
            keyType: 'number',
            description: 'Enter a number (1-25) for shift amount',
            validate: (key) => !isNaN(key) && key >= 1 && key <= 25
        },
        atbash: {
            keyType: 'none',
            description: 'No key required for Atbash cipher',
            validate: () => true
        },
        august: {
            keyType: 'none',
            description: 'No key required (Caesar cipher with shift of 1)',
            validate: () => true
        },
        affine: {
            keyType: 'text',
            description: 'Enter two numbers separated by comma (a,b) where a is coprime with 26',
            validate: (key) => {
                const [a, b] = key.split(',').map(Number);
                return a && b && isCoprime(a, 26);
            }
        },
        vigenere: {
            keyType: 'text',
            description: 'Enter a keyword',
            validate: (key) => /^[a-zA-Z]+$/.test(key)
        },
        gronsfeld: {
            keyType: 'number',
            description: 'Enter a sequence of numbers (e.g., 4312)',
            validate: (key) => /^\d+$/.test(key)
        },
        beaufort: {
            keyType: 'text',
            description: 'Enter a keyword',
            validate: (key) => /^[a-zA-Z]+$/.test(key)
        },
        autoclave: {
            keyType: 'text',
            description: 'Enter a keyword',
            validate: (key) => /^[a-zA-Z]+$/.test(key)
        },
        runningkey: {
            keyType: 'text',
            description: 'Enter a long text as key (must be at least as long as the plaintext)',
            validate: (key, text) => key.length >= text.length
        },
        hill: {
            keyType: 'text',
            description: 'Enter 4 numbers separated by commas for a 2x2 matrix (e.g., 5,17,4,15)',
            validate: (key) => {
                const nums = key.split(',').map(Number);
                return nums.length === 4 && nums.every(n => !isNaN(n));
            }
        },
        railfence: {
            keyType: 'number',
            description: 'Enter number of rails (2 or more)',
            validate: (key) => !isNaN(key) && key >= 2
        },
        route: {
            keyType: 'number',
            description: 'Enter the number of columns',
            validate: (key) => !isNaN(key) && key >= 2
        },
        myszkowski: {
            keyType: 'text',
            description: 'Enter a keyword',
            validate: (key) => /^[a-zA-Z]+$/.test(key)
        }
    };

    // Event Listeners
    cipherButtons.forEach(button => {
        button.addEventListener('click', () => {
            const cipherType = button.dataset.cipher;
            currentCipher = cipherType;
            
            // Update active button
            cipherButtons.forEach(btn => btn.classList.remove('active'));
            button.classList.add('active');
            
            // Update key input section
            const info = cipherInfo[cipherType];
            keyDescription.textContent = info.description;
            
            if(info.keyType === 'none') {
                keySection.style.display = 'none';
            } else {
                keySection.style.display = 'block';
                keyInput.value = '';
                keyInput.placeholder = info.description;
            }
        });
    });

    function processCipher(isEncrypt) {
        if(!currentCipher) {
            alert('Please select a cipher method first!');
            return;
        }

        const text = plaintext.value;
        if(!text) {
            alert('Please enter text to process!');
            return;
        }

        const key = keyInput.value;
        const info = cipherInfo[currentCipher];
        
        if(info.keyType !== 'none' && !info.validate(key, text)) {
            alert('Invalid key format! ' + info.description);
            return;
        }

        try {
            const cipher = ciphers[currentCipher];
            const result = isEncrypt ? cipher.encrypt(text, key) : cipher.decrypt(text, key);
            outputText.textContent = result;
        } catch(error) {
            outputText.textContent = 'Error processing text: ' + error.message;
        }
    }

    encryptBtn.addEventListener('click', () => processCipher(true));
    decryptBtn.addEventListener('click', () => processCipher(false));

    // Copy button functionality
    copyBtn.addEventListener('click', () => {
        const textToCopy = outputText.textContent;
        navigator.clipboard.writeText(textToCopy).then(() => {
            const originalTitle = copyBtn.title;
            copyBtn.title = 'Copied!';
            setTimeout(() => {
                copyBtn.title = originalTitle;
            }, 2000);
        });
    });
}); 