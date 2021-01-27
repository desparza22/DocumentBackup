#ifndef SECURETEXTS_H
#define SECURETEXTS_H

bool* secure_texts(char** texts, int numTexts, int textLengths);
bool* init_textSecurity(int numTexts, int textLengths);
int bits_required_to_secure_texts(int numTexts, int textLengths);

bool* secure_texts(char** texts, int numTexts, int textLengths) {
  bool* textSecurity = init_textSecurity(numTexts, textLengths);
}

bool* init_textSecurity(int numTexts, int textLengths) {
  int bitsRequiredToSecureTexts = bits_required_to_secure_texts(numTexts, textLengths);
  bool* textSecurity = malloc(bitsRequiredToSecureTexts*sizeof(bool));
}

int bits_required_to_secure_texts(int numTexts, int textLengths) {
  int bitsRequiredToSecurePerBit = bits_required_to_secure_nonsquare(numTexts);
  int bitsPerChar = 8;
  int bitsPerText = bitsPerChar * textLengths;
  return bitsRequiredToSecurePerBit * bitsPerText;
}

#endif
