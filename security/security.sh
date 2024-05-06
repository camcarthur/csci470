#!/bin/bash

# generate keys and trash the key output to terminal
openssl genpkey -algorithm RSA -out private_key.pem > /dev/null 2>&1
openssl rsa -pubout -in private_key.pem -out public_key.pem > /dev/null 2>&1


echo "Keys generated "

echo "Enter the message to encrypt (press Ctrl+D when done):"
input=$(</dev/stdin)

# Encrypt 
encrypted=$(echo "$input" | openssl pkeyutl -encrypt -pubin -inkey public_key.pem | base64)
echo "Encryption completed"

# Decrypt 
decrypted=$(echo "$encrypted" | base64 --decode | openssl pkeyutl -decrypt -inkey private_key.pem)
echo "Decryption completed"

echo "Input message: "
echo "$input"
echo "Encrypted message: "
echo "$encrypted"
echo "Decrypted message: "
echo "$decrypted"
