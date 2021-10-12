CBC / EBC Encryption of images

Step0: Save the BMP header of image (first 54 bytes)
head -c 54 night.bmp > nightHeader

Step1: Encrypt the entire image using cbc
openssl enc -aes-128-cbc -e -in night.bmp -out cbcnight.bmp -K 00112233445566778889aabbccddeeff -iv 0102030405060708

Step2: Save the body minus the header of the encrypted data (>54bytes)
tail -c +55 nightECB.bmp > nightBody

Step3: Reattach the original BMP header onto the encrypted data's body, recreating a proper bmp file
cat nightHeader nightBody> ecbNight.bmp