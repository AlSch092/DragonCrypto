//DragonCrypto - DLL File to be used with DragonClient for encrypting and decrypting packets on DragonNest (works on all world regions)
//Al Schwarz, 2015
//DragonNest uses static XTEA crypto for Village/TCPServer transactions, key changes each patch.
//m_TeaKey would look way better as a 2D Array as it's intended, but I wrote this code back in the noob days.

#include <Windows.h>
#define TEA_DELTA = 0x9E3779B9
#define TEA_BLOCKSIZE = 8
#define TEA_KEYCOUNT = 256

//4kb key + ptr at front = 4100 byte
unsigned char m_TeaKey[] = {0x7C,0x1E,0xEF,0x00,0xCB,0x49,0xD2,0x40,0x9D,0x2F,0xE5,0x13,0xD3,0xDD,0x16,0x04,0xB6,0x7D,0xF1,0x0A,0x3E,0x59,0x0B,0x1E,0x27,0x77,0xB6,0x2F,0x85,0x71,0x21,0x30,0xA0,0x9D,0xDF,0x75,0x70,0xD7,0x47,0x08,0xB2,0x7D,0x2A,0x6E,0xD2,0xF7,0xFB,0x00,0x1D,0x89,0x6B,0x47,0x9B,0xEA,0x9A,0x23,0x3F,0x6E,0xFE,0x2F,0x68,0xFE,0x11,0x45,0x62,0x33,0x2A,0x4F,0x77,0x8A,0x2D,0x5E,0xF4,0x04,0x49,0x39,0x92,0xDB,0x15,0x3E,0x50,0xFC,0xE4,0x4D,0xAC,0xCF,0x4A,0x13,0x48,0x47,0x5F,0x3F,0xCB,0x77,0x0D,0x12,0x9C,0xFC,0x68,0x6C,0x95,0xAC,0xB8,0x3D,0xFA,0xA8,0x7A,0x64,0x2A,0x15,0x1D,0x3F,0x8B,0x75,0x31,0x7F,0x6E,0xF5,0xC7,0x11,0x6A,0x4B,0x09,0x0F,0x13,0xB3,0x3F,0x4D,0xE4,0x95,0x32,0x47,0x09,0xA9,0x9A,0x10,0xFE,0x8E,0xE3,0x42,0xFE,0xFE,0xE4,0x34,0x54,0x7D,0xA5,0x30,0x96,0x48,0x0F,0x47,0x45,0xF3,0x99,0x44,0x20,0x81,0xCB,0x52,0x4A,0x5D,0x20,0x1B,0x60,0x24,0xA2,0x23,0x89,0x41,0xEB,0x5B,0xDA,0xC1,0xD9,0x70,0x26,0x58,0x84,0x3C,0x8B,0x46,0x52,0x71,0x1F,0xD6,0xF2,0x52,0x40,0xCA,0x8D,0x7D,0xE1,0x97,0xA7,0x01,0x36,0x9D,0xB4,0x24,0x30,0xA7,0x45,0x76,0xD1,0x17,0x59,0x37,0x64,0x25,0xB2,0x65,0x38,0x55,0x1C,0x73,0x9B,0x6F,0xEF,0x78,0x91,0xA7,0xC1,0x70,0x83,0x8F,0x1A,0x27,0xED,0x29,0x2B,0x5C,0xA4,0x7E,0x6F,0x12,0xED,0x18,0x92,0x7E,0xAE,0xF3,0xEF,0x6F,0xEB,0xF0,0x38,0x38,0x16,0xA7,0x9D,0x09,0x38,0x22,0x1A,0x6C,0x2A,0xB9,0x79,0x64,0xE7,0x10,0x29,0x04,0xE0,0xE9,0x47,0x09,0xF8,0xA8,0x0C,0x1F,0xC1,0xDE,0xC7,0x1C,0xE7,0x32,0x9E,0x4B,0xBC,0x52,0x3A,0x40,0x33,0x46,0x29,0x7F,0xAB,0x96,0xCD,0x19,0xA0,0xFD,0x8F,0x0D,0x29,0x53,0xCA,0x24,0x48,0x8D,0xF6,0x0D,0xD3,0x9A,0x99,0x3E,0x1F,0x14,0x9E,0x0E,0x06,0x61,0x3E,0x6A,0x55,0xA3,0xA9,0x53,0xD5,0x47,0x5F,0x2C,0xB0,0xD5,0x7E,0x22,0xCA,0xBE,0x8C,0x31,0x78,0x36,0x82,0x49,0xD7,0x3B,0x3C,0x65,0xD1,0xD1,0x54,0x2E,0x6F,0xA6,0x2C,0x49,0x4C,0x1A,0x55,0x0D,0x30,0xB9,0x4C,0x50,0x48,0x68,0xF1,0x7F,0x36,0xC0,0x6D,0x19,0x61,0x66,0x93,0x66,0xF6,0xBC,0x92,0x3C,0x5B,0xA8,0x6D,0x41,0x4C,0x8F,0x76,0x64,0x5F,0xE2,0xBA,0x10,0xAA,0x89,0x82,0x58,0x45,0xD7,0xCF,0x5B,0xD0,0x5E,0xDB,0x39,0xEB,0x76,0x26,0x30,0x26,0xCC,0x78,0x44,0x7F,0x33,0x77,0x47,0x07,0x5F,0xB4,0x6C,0x13,0xF4,0x8B,0x6B,0xC6,0x31,0xFC,0x60,0x87,0x8B,0x41,0x67,0x89,0x98,0x1C,0x21,0x08,0x5E,0xBC,0x44,0xBF,0xBD,0xDF,0x6F,0x42,0x3D,0x8E,0x67,0xA4,0x7F,0x2E,0x6E,0x11,0x8A,0x03,0x78,0x6A,0x9B,0xAD,0x0F,0xE9,0x58,0x37,0x67,0xDF,0x7A,0x4F,0x4D,0xA4,0x79,0x74,0x60,0x0F,0xDD,0x4A,0x54,0xB1,0xF7,0xD5,0x61,0x97,0x07,0xB9,0x4F,0x1F,0x5D,0x18,0x49,0xAB,0x8D,0x2C,0x0F,0x66,0xAE,0xC5,0x27,0x66,0x57,0x47,0x22,0xBA,0x96,0xE2,0x50,0x4C,0x1C,0xEE,0x14,0xF3,0x95,0x54,0x71,0xF3,0x87,0x88,0x23,0x19,0xAE,0x69,0x06,0x60,0xF9,0x01,0x08,0xD2,0xA9,0x96,0x06,0x9A,0xC6,0x71,0x1C,0xD1,0xB2,0x64,0x1A,0x30,0x12,0x3C,0x7D,0x3C,0x2F,0xE9,0x68,0x14,0x74,0x2F,0x65,0xE6,0x98,0xDB,0x19,0x95,0x94,0xA5,0x39,0x0E,0x03,0x9B,0x03,0xBC,0x9B,0xBF,0x3C,0xE5,0x32,0xA5,0x13,0xA5,0x8A,0xFB,0x43,0xD9,0x66,0xD9,0x2C,0xA9,0xE4,0xA9,0x01,0x45,0x09,0xD1,0x17,0xD1,0x1E,0x62,0x4D,0x0D,0x4F,0x3A,0x19,0x97,0x8B,0x3F,0x77,0x2B,0x4F,0xCF,0x27,0xAF,0x48,0xEE,0x29,0x74,0xBE,0xBF,0x17,0xD6,0x97,0xAA,0x15,0xED,0x12,0x5E,0x4B,0xBA,0xD6,0x23,0x7A,0x6F,0xC6,0xCD,0x43,0x8C,0x63,0x91,0x26,0xB8,0x4C,0x5B,0x6E,0xB9,0xED,0x78,0x27,0x38,0x1D,0xA5,0x17,0xF5,0x68,0xF2,0x7A,0x61,0xFE,0xB2,0x4C,0x8C,0x25,0x92,0x33,0xC0,0x95,0x4A,0x68,0xE4,0x9F,0x0D,0x63,0x32,0x9F,0x8D,0x66,0x76,0xC1,0x75,0x67,0xF0,0xCA,0x58,0x44,0xC4,0x61,0x0D,0x46,0xBB,0x22,0xBD,0x5C,0xB2,0x57,0x24,0x4E,0xDE,0x2B,0xBD,0x1D,0xBB,0xB9,0x12,0x59,0x0A,0x4E,0x6D,0x2F,0x53,0x61,0x8C,0x4F,0x68,0x56,0x65,0x4B,0xD0,0x20,0x00,0x4D,0xA9,0xD9,0x40,0x5B,0x9B,0x7A,0x3E,0x31,0x39,0x72,0x37,0x4B,0x4E,0xCA,0x70,0x5A,0x12,0xAD,0x4A,0x03,0xF5,0xA9,0xE1,0x10,0x75,0x2A,0xF1,0x0D,0x80,0x2B,0x7C,0x52,0x9C,0x4C,0xAA,0x1F,0xAD,0xC0,0x2E,0x79,0xD9,0x03,0xF0,0x50,0x50,0x36,0x0B,0x2C,0xE5,0xFD,0x96,0x68,0x5E,0x8A,0x74,0x25,0xBE,0xCF,0x85,0x0E,0x68,0x4C,0x28,0x72,0xB8,0xD9,0x09,0x1C,0xCE,0x14,0xA0,0x18,0x28,0x46,0x4D,0x6B,0x96,0x5F,0x9B,0x35,0x27,0x0D,0x32,0x1E,0x81,0xF3,0x6A,0x39,0x79,0x11,0xD0,0x1C,0xA3,0x2D,0xAC,0x36,0xA4,0x97,0xF4,0x4E,0x87,0x31,0x01,0x7D,0xFC,0x7B,0x91,0x74,0xF9,0xF6,0xE1,0x22,0x88,0x41,0x23,0x7D,0x66,0x61,0x0F,0x37,0x9A,0xF0,0x51,0x34,0x07,0x69,0xD3,0x40,0xE4,0x40,0x69,0x1B,0x67,0xC2,0xBF,0x28,0x3E,0xF4,0xA7,0x27,0xCA,0x4B,0x33,0x34,0x49,0xA0,0xD5,0x69,0x74,0xCE,0x44,0x6B,0xEA,0xCF,0x7F,0x46,0xA3,0xD4,0x6A,0x4E,0xD6,0x02,0xE8,0x5F,0x31,0x02,0xF2,0x03,0xBD,0x98,0x41,0x04,0x70,0x8F,0x39,0x1A,0xBC,0xF1,0x05,0x10,0xD7,0x08,0x3D,0x5A,0x0F,0x8B,0xBF,0x25,0xE6,0x18,0x30,0x32,0x89,0x4D,0x6F,0x06,0x21,0x39,0xE0,0x19,0x38,0x4F,0x03,0x35,0x1A,0x51,0x26,0x7A,0x6A,0xA5,0x82,0x7A,0x8A,0xCA,0x36,0x67,0x4F,0x3C,0xA0,0x6C,0x24,0xDD,0xF2,0x4C,0x97,0x9B,0x31,0x5B,0x77,0x53,0xDA,0x2D,0x52,0x59,0x68,0x1D,0xCC,0x38,0x69,0x79,0xA9,0xAA,0x17,0x54,0x8D,0x19,0x57,0x14,0xB7,0xF8,0xBC,0x5F,0x34,0xA2,0x70,0x68,0x85,0x77,0x63,0x7B,0x5F,0x03,0x99,0x3F,0x0D,0x88,0xCC,0x7C,0x37,0xD9,0x97,0x00,0xF0,0x35,0xCC,0x39,0x17,0x65,0x2E,0x69,0x9B,0xA1,0x8A,0x27,0x26,0xC0,0x39,0x1E,0x4B,0x33,0xD8,0x24,0x90,0xDB,0x47,0x05,0x1A,0x62,0x3F,0x60,0x05,0xDE,0xAC,0x30,0xBA,0x4E,0xD0,0x3D,0x91,0x74,0x40,0x32,0xA6,0x6D,0xAF,0x0A,0xB5,0x79,0xDA,0x08,0xBA,0xEB,0xC4,0x03,0x40,0x02,0x7E,0x2C,0xEC,0xB3,0xBE,0x7B,0x65,0x27,0xA6,0x41,0x2C,0x50,0x73,0x66,0xBC,0x85,0xEB,0x55,0xAB,0xC1,0x0F,0x76,0x4D,0x4D,0xFA,0x0E,0xBA,0x8B,0x2D,0x60,0x61,0x46,0x35,0x7E,0xA1,0x4A,0x32,0x41,0x2D,0x64,0xAF,0x0E,0xA0,0xEF,0x0B,0x23,0x92,0x3D,0xFA,0x0D,0xDF,0xE3,0x3C,0x38,0xEE,0x4D,0x41,0x79,0x8D,0x4B,0x91,0x29,0x77,0x3D,0xDD,0x5E,0xD7,0x46,0x23,0x5D,0xC4,0xCF,0xAA,0x2E,0x13,0x3E,0x88,0x7A,0x3E,0x40,0x77,0x60,0xDB,0x5F,0x8C,0x0E,0x1D,0x81,0xCB,0x23,0x85,0x9A,0x98,0x07,0xA0,0xAA,0x8A,0x02,0x57,0xA2,0x6F,0x5B,0x91,0xA6,0x76,0x11,0xE2,0x14,0xCE,0x28,0x2B,0x6B,0xE3,0x75,0x81,0xB9,0x5F,0x17,0x25,0x75,0x82,0x74,0x71,0x7C,0xA5,0x07,0x3F,0x36,0xC0,0x74,0x20,0x9B,0x08,0x51,0xD6,0x9B,0xD5,0x69,0xC2,0x08,0x59,0x2F,0x13,0xD9,0x2D,0x61,0xE0,0xB6,0x5D,0x3A,0x22,0x3A,0xF0,0x72,0x42,0xEE,0xC7,0x65,0x44,0xF0,0x6D,0x4B,0x93,0x6E,0x5F,0x1F,0xE7,0xE6,0x0B,0x7B,0x45,0xE3,0x33,0x2A,0xB9,0x75,0xFE,0x54,0x1A,0x10,0xCD,0x17,0xB1,0xB2,0xC4,0x4A,0x7C,0xB6,0x6E,0x6A,0x8B,0x96,0x2D,0x60,0xF1,0x56,0xF5,0x57,0xE0,0x03,0x3F,0x22,0xFA,0x8F,0x87,0x51,0xF9,0x8E,0x77,0x69,0x59,0x3E,0x88,0x51,0xED,0x84,0x71,0x0A,0xE4,0x62,0x6E,0x31,0x80,0x93,0xEE,0x66,0x0B,0x6F,0x7E,0x23,0x92,0xCD,0xF9,0x04,0xBF,0x9E,0xA8,0x2D,0xAA,0x9F,0x08,0x47,0x2F,0x84,0xFA,0x11,0x31,0x4C,0x14,0x17,0x39,0x0D,0x02,0x35,0xD1,0xC8,0xE2,0x07,0x63,0xAE,0x3A,0x13,0x2F,0x21,0x0B,0x15,0x8E,0x50,0x14,0x52,0x9C,0x24,0xBC,0x32,0x92,0xBF,0xD8,0x1F,0x33,0x13,0x2D,0x59,0x1F,0x33,0xC6,0x1E,0x20,0x3E,0x63,0x4A,0xAE,0xD4,0xD2,0x5A,0x3A,0x25,0x10,0x1C,0xAD,0xFB,0xD7,0x01,0x63,0x4E,0x4A,0x6D,0xCA,0xEF,0x51,0x45,0xD6,0xEF,0xF5,0x7F,0x26,0x35,0x14,0x14,0xBF,0x5C,0x84,0x3A,0x94,0x42,0x23,0x64,0x98,0xBC,0xFB,0x25,0xC3,0x44,0x32,0x16,0x7F,0xA4,0x91,0x0C,0x72,0xBF,0xB3,0x10,0x53,0x0A,0xD9,0x3C,0x66,0x05,0x28,0x15,0x5E,0x62,0xC1,0x57,0x1F,0x34,0x26,0x42,0xAE,0x90,0x5E,0x18,0x2E,0x0C,0xB1,0x43,0x1B,0xF8,0x70,0x48,0x76,0xBF,0xF4,0x67,0x81,0x54,0xAD,0x27,0x63,0xA1,0x5E,0x56,0xC5,0x9F,0xF2,0x1B,0x51,0x62,0xF3,0x46,0xF5,0xEB,0xDC,0x28,0xE6,0xE2,0x1B,0x2E,0x5A,0x74,0xDF,0x2E,0xA8,0x04,0xE2,0x27,0xE3,0x3B,0x02,0x70,0x6F,0xAE,0xE9,0x57,0xB8,0x81,0x31,0x6F,0xE4,0x95,0x91,0x43,0x55,0x8D,0xED,0x60,0x03,0x4E,0x60,0x2A,0x52,0x51,0x24,0x5F,0x92,0xE2,0xC3,0x7C,0xF9,0xCE,0x9B,0x50,0x83,0x07,0x76,0x37,0x02,0x4D,0xA2,0x1E,0x4A,0xF1,0x4C,0x3D,0xF7,0x5B,0x0A,0x0C,0x10,0xD3,0x9B,0x0B,0x5E,0xBC,0x31,0x0C,0x9A,0x4D,0x3C,0x03,0x00,0x1E,0xC7,0x57,0xD6,0x2F,0x93,0x43,0x54,0x12,0x90,0x28,0xD9,0xCA,0xBB,0x72,0x20,0x4E,0xCA,0x6F,0x74,0x89,0x3D,0x07,0x9F,0x90,0xFF,0x1F,0x0A,0xF0,0xF0,0x45,0x18,0xB5,0x03,0x7F,0x0B,0x4C,0x28,0x69,0xEF,0x58,0x23,0x38,0xC5,0x24,0xDC,0x16,0x81,0xB4,0x4E,0x6A,0xC5,0x83,0x4D,0x2E,0x5D,0x42,0x42,0x01,0x7C,0x55,0x6F,0x41,0x0A,0x4A,0x01,0x2D,0x2E,0x65,0x0E,0x72,0xC6,0x06,0x2F,0x32,0x13,0xF2,0x99,0x33,0x45,0x2C,0x0A,0x74,0x56,0xD4,0xDF,0x0B,0xAD,0xBD,0xC6,0x54,0x94,0x66,0x91,0x6F,0xAB,0xCE,0x5D,0x65,0xD4,0xF9,0xEE,0x09,0xFC,0x05,0xE4,0x7C,0x57,0x0E,0xE7,0x32,0xAA,0x65,0x06,0x11,0x79,0x32,0x77,0x50,0x67,0xC3,0x15,0x62,0x02,0xDF,0x65,0x0B,0x40,0x96,0xD6,0x6E,0x1C,0xB3,0x06,0x47,0x05,0x7E,0x69,0x7C,0x8A,0x9E,0x74,0x7F,0x2A,0x81,0xCD,0x03,0x2A,0xC6,0xBA,0x63,0x4A,0x94,0x39,0x6B,0x6F,0x1A,0x33,0x4C,0x8E,0x90,0x86,0x12,0x2D,0xE9,0xE5,0x2B,0xC4,0x4F,0xCC,0x74,0x52,0x89,0xB0,0x61,0x69,0xDD,0x4D,0x13,0x58,0x69,0xA0,0x29,0xB9,0x5E,0xE2,0x60,0xE9,0x49,0xE8,0x7F,0x27,0x9E,0x1B,0x01,0x57,0x1A,0x4B,0x24,0xB4,0xC8,0xDB,0x66,0xD8,0xB8,0xEC,0x0F,0xFF,0xDF,0xC4,0x40,0x2B,0x41,0x5E,0x6D,0x75,0x88,0xC1,0x0D,0x0F,0x05,0xC4,0x53,0x98,0xBB,0xE8,0x17,0x6B,0xB1,0x3A,0x1F,0x7D,0x24,0x83,0x71,0x77,0xD4,0xC4,0x4A,0xFE,0xCE,0x98,0x4E,0x32,0x87,0xB6,0x05,0xCE,0xE2,0x17,0x77,0xF2,0x25,0xEE,0x61,0xFB,0x40,0xF5,0x66,0x75,0x9A,0x2A,0x23,0xB7,0x59,0x89,0x60,0xD7,0xFD,0xB7,0x30,0x8E,0x46,0x65,0x6C,0x4F,0x0F,0x8A,0x11,0x43,0x94,0xD1,0x44,0xCA,0xCE,0x67,0x73,0x78,0x01,0x1D,0x4D,0xF3,0x02,0x60,0x15,0xF0,0xDE,0x35,0x35,0x9B,0x32,0x3E,0x2E,0xE2,0x5F,0x28,0x3A,0x8B,0x36,0xD8,0x74,0x28,0x30,0x48,0x1B,0xA2,0xF5,0x66,0x5C,0xAC,0x68,0x5C,0x56,0x1F,0x30,0x5C,0x54,0xD0,0x2C,0xF7,0x75,0xF0,0x18,0xA8,0x7B,0xA4,0x0D,0xDC,0x16,0x87,0x46,0xC8,0x54,0xAE,0x96,0x1A,0x49,0xFE,0x56,0xF7,0x0C,0x4B,0xD7,0xAE,0x5D,0x6B,0xCD,0x00,0x2B,0x31,0xEC,0x46,0x7A,0xA7,0x0F,0x7F,0x17,0xDA,0x4D,0x2D,0x07,0x54,0xBD,0xD5,0x11,0x12,0x28,0x5F,0x63,0x23,0xDA,0xA5,0x34,0xA9,0x57,0x56,0x6E,0x10,0xCE,0xF6,0x43,0x7E,0xC0,0x21,0x5B,0xAC,0xAA,0x25,0x1C,0x64,0x74,0xC8,0x5A,0xE9,0xBA,0xA2,0x6D,0x46,0xD3,0x81,0x71,0x2F,0x27,0x34,0x77,0x24,0x6B,0xFE,0x72,0x3A,0x2A,0x6C,0x28,0x1B,0xD6,0x1F,0x02,0x73,0xAE,0xFB,0x2B,0x12,0x6F,0xE0,0x0C,0xF9,0x36,0xAE,0x50,0xE5,0x26,0x25,0x2A,0xA5,0x0D,0x07,0x63,0xE8,0x41,0xFD,0x49,0x58,0x4E,0x0A,0x16,0xE3,0x51,0x5D,0x10,0xA5,0xD6,0x81,0x17,0xD1,0xC9,0x04,0x30,0x47,0x9A,0x15,0x79,0x6E,0xC6,0xE7,0x42,0x72,0xB2,0x23,0x25,0x25,0xE5,0xD5,0x37,0x7F,0x15,0x12,0x2C,0xCA,0x02,0x58,0x4D,0xD3,0x68,0x92,0x12,0xD9,0x6B,0x2C,0x0C,0x39,0x1C,0x53,0x21,0x36,0xCE,0x11,0x34,0x82,0xD4,0x25,0x48,0xDE,0xFB,0x89,0x15,0x2D,0x8B,0xD6,0x62,0x1B,0x54,0x75,0x3B,0xA2,0x40,0xA3,0x30,0xD9,0x31,0x0E,0x37,0xC9,0x1E,0x00,0x05,0x1F,0x75,0x38,0x24,0xA8,0x14,0xA7,0x56,0xBE,0x34,0xF9,0x27,0x71,0x4B,0x6F,0x6A,0xDF,0x76,0xDF,0x5C,0x43,0xB2,0x8C,0x31,0x22,0x07,0x4D,0x40,0xF6,0xD5,0xE4,0x4A,0x2A,0xC7,0x14,0x4F,0x0A,0x03,0xBB,0x2D,0x72,0x2B,0x3D,0x57,0x23,0x79,0x16,0x39,0x85,0x99,0x26,0x39,0x8D,0xEE,0xB1,0x0D,0xB4,0x09,0xE0,0x77,0x7C,0x99,0x4F,0x2A,0xD0,0x88,0xEF,0x54,0x83,0x06,0xC3,0x2A,0xBF,0x0B,0xE1,0x58,0x84,0x57,0x30,0x45,0x63,0x76,0x7F,0x72,0xAE,0x6F,0x45,0x4A,0x5C,0xC3,0x6F,0x40,0x08,0xDB,0x86,0x40,0x4E,0x6E,0x49,0x27,0xE5,0xFA,0x4B,0x44,0x57,0xA2,0xAA,0x2E,0x7D,0x2E,0x93,0x4A,0xC3,0x0C,0x68,0x6F,0xB6,0x87,0x62,0x41,0x8A,0xDB,0x54,0x79,0x94,0x0B,0xBE,0x6F,0xB0,0x24,0xDF,0x21,0x7C,0xAD,0x27,0x78,0x78,0xDB,0xFE,0x7C,0x4F,0x6A,0x93,0x21,0x98,0xA1,0x86,0x71,0x99,0x8A,0x0C,0x41,0x25,0x6B,0xC9,0x3A,0x6F,0xCE,0x7E,0x16,0x29,0x6F,0xBD,0x45,0x75,0xB3,0x04,0x24,0xD7,0x29,0x8E,0x4B,0xB0,0x1A,0x68,0x25,0x29,0xF1,0xAB,0x16,0x70,0x9C,0xD8,0x1E,0x2D,0x36,0xDB,0x27,0xD2,0x59,0xF5,0x74,0x86,0xC0,0x2E,0x0D,0x48,0x3A,0x9F,0x7D,0xBC,0x13,0x2C,0x02,0x63,0xF1,0x8B,0x4D,0xDC,0x0E,0x2B,0x3D,0x5F,0x98,0xA3,0x4E,0x4D,0x35,0xA9,0x79,0x9C,0x1F,0x52,0x5F,0xC4,0x19,0x1B,0x66,0x46,0xB6,0x70,0x15,0x2F,0x79,0xDD,0x43,0x90,0xC0,0x85,0x58,0xF9,0xB2,0x4F,0x17,0xD9,0xB1,0xC4,0x6D,0x6F,0x38,0xEA,0x02,0xD0,0x41,0xD0,0x77,0x9D,0xD8,0x94,0x4F,0x3B,0x27,0x1D,0x0A,0x6E,0x5C,0xB4,0x52,0x3C,0x78,0x22,0x30,0x87,0x10,0x18,0x2D,0x00,0x4D,0x89,0x21,0x00,0x8E,0xAC,0x25,0x79,0x4F,0x0C,0x75,0xAF,0x85,0xAB,0x3E,0x2C,0x60,0xCC,0x0E,0x31,0xFE,0x0F,0x0E,0x0A,0x86,0x1A,0x78,0xE3,0x6B,0x83,0x0A,0xDC,0x00,0x0B,0x07,0x58,0x9F,0xF4,0x69,0xDB,0x7A,0x36,0x38,0x6D,0x8A,0x62,0x28,0x0E,0x56,0xB0,0x05,0x41,0xE4,0x93,0x1A,0x47,0x07,0xF3,0x68,0xE8,0x70,0xC9,0x1C,0x68,0xAA,0x2D,0x46,0x47,0xF8,0xFA,0x65,0xCF,0x9F,0xDB,0x48,0xBB,0xD9,0x35,0x22,0xE8,0x0F,0xE8,0x2E,0x6D,0xF7,0x91,0x16,0xCD,0x43,0x32,0x20,0xD5,0x04,0xE8,0x4C,0xD2,0x84,0x13,0x6E,0x57,0x5E,0xE3,0x36,0x1E,0xC0,0x48,0x31,0xE8,0x73,0xE3,0x5C,0xF6,0x14,0x6D,0x7D,0xF9,0xD5,0xB2,0x50,0xCF,0x1A,0x48,0x29,0xB1,0x99,0xFF,0x6C,0xCB,0x81,0xF0,0x2A,0x6B,0xF8,0x7F,0x7E,0x30,0x6C,0xA2,0x08,0x6A,0xE2,0x65,0x3B,0x1C,0x46,0xAC,0x44,0x29,0x19,0x53,0x43,0x5D,0x8B,0x82,0x48,0x99,0x5D,0x62,0x57,0xA0,0xE3,0x80,0x2E,0x86,0x77,0xAF,0x4B,0xB7,0xB2,0x54,0x77,0xB2,0x84,0xF2,0x29,0x1D,0xDD,0x3C,0x16,0x7B,0x3D,0x13,0x08,0x79,0x37,0x7E,0x45,0xE6,0xC9,0x80,0x43,0x0F,0xD5,0x23,0x6C,0x64,0x88,0x5A,0x0A,0xD9,0x29,0x41,0x65,0xE3,0x8F,0x4D,0x3D,0xA9,0x57,0x47,0x48,0x89,0x28,0x53,0x3A,0x10,0x2A,0xBF,0x3B,0x78,0x8E,0x69,0x50,0x96,0x8B,0x27,0x4F,0x15,0xDD,0x05,0x0B,0xD1,0x80,0x6F,0x5B,0xCD,0xA3,0x4B,0x66,0x68,0x9A,0x45,0x12,0x84,0x5E,0x81,0x51,0x36,0x23,0xBC,0x75,0x11,0x5D,0xCD,0x61,0x61,0x92,0x89,0x22,0x36,0x9C,0x5A,0x48,0xC7,0x22,0x4B,0x62,0xB9,0x58,0x1D,0x39,0x9A,0x56,0x65,0x10,0xE4,0x06,0xE6,0x13,0x0D,0x87,0x18,0x1A,0x05,0xEF,0x50,0x58,0xA1,0xD3,0x10,0x6D,0xB6,0x67,0xE9,0x7C,0xE1,0x46,0x00,0x4C,0xC9,0x54,0x4D,0x17,0x40,0xB2,0x95,0x38,0x3E,0x2D,0x4C,0x41,0x6F,0x2B,0x07,0x56,0x75,0xD3,0x8D,0x08,0x28,0xCB,0x5A,0x27,0xA1,0xF2,0x46,0x6D,0x5D,0x42,0x04,0x76,0x82,0x83,0x9C,0x50,0x7A,0xE3,0xB3,0x20,0x22,0x7A,0xD0,0x3F,0x33,0x44,0x1A,0x26,0x06,0x28,0xF5,0x25,0x91,0x1F,0x9C,0x64,0xE4,0xE5,0x4A,0x7D,0x15,0x88,0x2A,0x2D,0x6F,0xCD,0xE9,0x10,0x56,0xA1,0x64,0x77,0x63,0x4E,0x5B,0x49,0x5E,0x7B,0xB5,0x20,0xC7,0x0D,0x99,0x4C,0x4A,0xE1,0x4D,0x33,0x99,0x9C,0x1F,0x75,0x43,0x4F,0xCE,0x29,0xB9,0xCF,0x6F,0x1C,0x98,0x16,0xA7,0x7E,0x1E,0xCE,0x15,0x1D,0xF9,0xBD,0x7B,0x1A,0x25,0xC4,0x48,0x08,0xEC,0x99,0xFB,0x0D,0xB3,0x4E,0x7D,0x61,0x27,0x59,0x7F,0x2F,0x48,0x31,0x80,0x32,0xEB,0x12,0xFE,0x58,0x63,0x58,0x25,0x1C,0xA6,0x90,0x74,0x70,0xB2,0xC8,0x1D,0x44,0x6B,0x20,0x4C,0x10,0x08,0xFE,0xF8,0x0B,0xB9,0xD8,0x7B,0x63,0x34,0x05,0x30,0x7D,0x43,0x41,0x2C,0x02,0x16,0x99,0x08,0x17,0x28,0x1C,0x22,0x17,0xA4,0xB4,0x18,0x12,0x58,0x8B,0x82,0x6F,0x7A,0xC1,0xED,0x0A,0x4E,0xBA,0x2F,0x39,0x2D,0xA0,0x89,0x74,0x80,0x56,0x4A,0x50,0x8F,0xA1,0x63,0x7A,0x35,0xC6,0xEC,0x5D,0xDB,0x1C,0x60,0x2F,0x69,0xE2,0xBF,0x46,0xBA,0x4F,0x86,0x3B,0x03,0x10,0xB2,0x30,0xA2,0x74,0xCA,0x38,0x05,0xEF,0xD0,0x15,0x91,0x8A,0x3D,0x75,0xE8,0xB4,0xA9,0x13,0x55,0x53,0x8A,0x61,0x53,0x43,0xED,0x7F,0xD0,0x94,0x78,0x6C,0x3B,0xA6,0xBF,0x2F,0x82,0x14,0x1D,0x6F,0x5A,0xBC,0x8B,0x1B,0x97,0xE3,0x6C,0x09,0xD2,0x87,0xDB,0x24,0xFE,0xB1,0x59,0x3C,0x2A,0x0E,0x7E,0x41,0x05,0x56,0x3C,0x41,0xD4,0xC1,0xAD,0x34,0xA5,0x7A,0xF1,0x34,0xF9,0x19,0xF9,0x19,0x34,0x8A,0x5F,0x08,0x03,0xEA,0xEE,0x5B,0x9E,0x23,0xF8,0x67,0x1A,0x51,0x21,0x0C,0x13,0x19,0x44,0x46,0x25,0x27,0xE2,0x73,0x2B,0xA0,0x3B,0x25,0xB0,0x78,0xF7,0x0A,0xE7,0xA6,0x9A,0x2B,0xFC,0x6C,0x93,0x26,0xD2,0xD5,0xDD,0x5F,0xC7,0x0F,0xFA,0x62,0xA7,0x7D,0x46,0x34,0x27,0x1D,0xDD,0x5C,0x67,0xCC,0x6A,0x2D,0x4D,0x3B,0x25,0x4A,0x65,0x08,0x3E,0x51,0x0B,0x63,0xAF,0x5C,0x3C,0x4B,0x6B,0x00,0x0B,0x72,0xC9,0x72,0x20,0x2B,0xC7,0x5C,0x40,0xC5,0x06,0x25,0x29,0x7C,0x90,0x7A,0x1F,0x5E,0xB5,0x7B,0x60,0x05,0x39,0x06,0xD0,0xD9,0xD2,0x79,0x97,0x9F,0x80,0x16,0xD5,0xC5,0x47,0x13,0x72,0x2B,0xA2,0x34,0xD9,0xB9,0x96,0x29,0xEB,0xFF,0x5F,0x10,0xE7,0xE1,0xC0,0x38,0x3D,0xA2,0x55,0x2B,0x9C,0x07,0xDC,0x63,0x45,0x55,0x19,0x6A,0xBA,0x6E,0x39,0x27,0x8D,0x44,0xB7,0x76,0xF8,0xDA,0xEB,0x7A,0xB3,0xC0,0x55,0x69,0x88,0xC9,0x27,0x44,0x3F,0x92,0x70,0x21,0x07,0xD3,0xEC,0x6D,0xCA,0x14,0x87,0x30,0xF0,0x21,0xB5,0x40,0xAC,0x77,0x88,0x29,0xA4,0xA7,0xDC,0x38,0x84,0x3E,0x95,0x5F,0xBF,0x39,0x01,0x4B,0x3C,0xFF,0x9D,0x4B,0x9D,0xAC,0xD2,0x43,0x9E,0xE8,0xB7,0x50,0x36,0xF7,0x83,0x19,0xD1,0xB4,0xB3,0x63,0x70,0x27,0x26,0x42,0xB3,0xD0,0x53,0x18,0x42,0x62,0xF5,0x2C,0xD5,0xD2,0x57,0x65,0xF4,0xA3,0xED,0x18,0x14,0x56,0x4B,0x76,0x73,0xDC,0x84,0x49,0x11,0xF7,0x46,0x1D,0x46,0xB2,0x14,0x2A,0x63,0x5A,0xBB,0x42,0x9E,0x21,0x4E,0x2F,0x47,0xAD,0x16,0x1C,0xDA,0x3B,0xCD,0x7F,0x2B,0x80,0x58,0x2C,0x4A,0xDC,0x4B,0x76,0x39,0xBD,0xA7,0x56,0x0F,0x7C,0xD2,0x2C,0x43,0x82,0xEA,0x39,0xAB,0xC3,0xFE,0x38,0xB3,0xB2,0x51,0x2A,0xC7,0xC9,0x56,0x33,0x07,0x1B,0xFB,0x47,0x39,0x9B,0x6A,0x06,0x1A,0xEE,0xC5,0x7B,0x8A,0x2C,0x4B,0x4B,0xDF,0x27,0xC3,0x7B,0x9E,0x48,0x15,0x5E,0x09,0x92,0xDE,0x68,0x96,0x47,0xA7,0x4F,0x74,0xCA,0x9A,0x12,0xCB,0xB9,0x64,0x1B,0x8E,0xB1,0x51,0x03,0xBA,0x9B,0xC6,0x1B,0xF2,0xFE,0x56,0x5A,0x62,0x42,0xFF,0x0B,0x7C,0x92,0x04,0x3F,0x37,0xCE,0x1C,0x27,0xDA,0x97,0xCF,0x15,0xB5,0xA4,0x85,0x19,0xE5,0x54,0x2F,0x67,0xB7,0x99,0x25,0x44,0x0F,0xED,0xF3,0x6F,0x4B,0x74,0xFC,0x37,0x65,0x55,0xBD,0x73,0x41,0xC5,0x76,0x69,0x94,0x2E,0x54,0x3E,0x67,0xD5,0xC4,0x5C,0xBE,0xB9,0xA6,0x69,0x43,0xE7,0xFB,0x49,0x9B,0x23,0xF0,0x24,0x44,0xFC,0x13,0x22,0x2D,0xAD,0xDE,0x6A,0xC9,0x9C,0xF6,0x30,0xE2,0x5A,0x6E,0x16,0xEF,0xFA,0x9A,0x2F,0xC8,0xF8,0xF5,0x4B,0x99,0x32,0x33,0x19,0x43,0x79,0xE0,0x2B,0xCE,0x7E,0xBE,0x79,0x67,0x30,0xA7,0x77,0xA6,0xE9,0xCD,0x54,0xEA,0xF2,0xF7,0x2B,0x86,0xAD,0x10,0x74,0xF3,0x95,0xBD,0x64,0x7A,0x87,0x5D,0x27,0x4D,0xDC,0x08,0x4A,0x78,0x09,0x58,0x27,0x99,0x98,0xED,0x77,0xC4,0x90,0x43,0x0A,0x53,0x21,0xF6,0x64,0x9F,0x88,0x81,0x06,0xA7,0x70,0x4A,0x32,0x67,0xCA,0x0A,0x2C,0x35,0xF2,0x05,0x2E,0x59,0xF3,0x9D,0x6A,0xF8,0x3A,0x8F,0x68,0x86,0x8E,0xDA,0x09,0xEC,0x53,0x99,0x4F,0x72,0x92,0x92,0x0A,0x22,0x69,0xD0,0x13,0x70,0xB7,0x5C,0x3F,0x7C,0x47,0xC0,0x0D,0xED,0x4B,0x90,0x55,0xE6,0x96,0x2E,0x51,0xBF,0x0A,0x29,0x41,0xE3,0xAF,0xCE,0x76,0x5C,0xE2,0xC4,0x02,0xFC,0xBB,0xB7,0x37,0x36,0x9F,0x15,0x4B,0x41,0xEE,0xFA,0x73,0x9B,0xE5,0x41,0x7E,0x84,0x73,0x67,0x7B,0x95,0x53,0xD3,0x1E,0x74,0xD4,0xF5,0x7A,0x10,0x5C,0xB1,0x50,0x60,0xF7,0xE9,0x34,0xD9,0x37,0x05,0x1F,0x8D,0x73,0x63,0x6B,0x3A,0x3D,0x06,0x48,0xED,0xE2,0x58,0x41,0xFD,0xBE,0x05,0x58,0x22,0xB8,0xC0,0x62,0x9B,0x34,0xC1,0x3A,0xEE,0x1A,0x9F,0x4C,0xAA,0x93,0x81,0x64,0x58,0x8E,0x37,0x22,0x38,0x3E,0x3A,0x4E,0xDC,0xBF,0xB9,0x4B,0xF8,0x53,0xAD,0x46,0x0F,0x84,0xBE,0x1A,0x58,0x93,0xEE,0x79,0x5D,0x16,0x98,0x3C,0x75,0xDF,0xC4,0x34,0x97,0x2B,0xFC,0x15,0xFF,0x72,0x58,0x47,0xB5,0xB7,0x5D,0x64,0xFB,0x03,0xE2,0x62,0xDD,0x36,0xAF,0x40,0x7F,0x26,0xF7,0x07,0x9C,0x8F,0x22,0x7C,0x8B,0xF5,0x37,0x63,0xAB,0x8D,0x3A,0x3F,0x52,0x5F,0xEE,0x79,0xF7,0x48,0x00,0x48,0xD8,0xD1,0xEF,0x44,0x20,0x55,0xA1,0x15,0x2D,0xC5,0x98,0x6D,0x89,0x69,0x3D,0x72,0xAB,0x9D,0xF2,0x04,0xFF,0x8C,0x3C,0x22,0xB6,0xF2,0x9F,0x4C,0xBE,0x40,0x0C,0x77,0x97,0x85,0xC4,0x65,0xEA,0xB4,0xC0,0x34,0x64,0x3D,0x80,0x57,0x3A,0xB4,0xD2,0x0F,0x34,0x7F,0xB7,0x48,0x3A,0x3B,0x1A,0x05,0xF3,0x85,0x2A,0x48,0xFE,0x31,0xDB,0x46,0x3D,0x17,0xD4,0x18,0x44,0x97,0x60,0x66,0xCD,0xA5,0xD1,0x4E,0xF8,0x94,0x29,0x0C,0x02,0xA9,0x8E,0x23,0x63,0xA8,0x43,0x56,0xC9,0xEE,0xF8,0x29,0x68,0x20,0x5C,0x3A,0x59,0x1E,0x5A,0x67,0xB5,0xFC,0x86,0x0D,0x7E,0x03,0x78,0x77,0x6D,0x88,0x9E,0x15,0x74,0xB3,0x95,0x6B,0xF8,0x0B,0xAA,0x52,0x83,0xB7,0x82,0x26,0x4E,0xCB,0x05,0x48,0xA1,0xFC,0x4C,0x40,0x03,0x69,0x45,0x43,0x13,0x19,0x6D,0x71,0x29,0xD8,0xDF,0x03,0x9E,0x27,0xAC,0x64,0x9E,0x63,0x7B,0x5A,0x2B,0x1D,0x5A,0x79,0x23,0xEF,0xF5,0x27,0x16,0x20,0xC6,0x24,0xAA,0x84,0xCA,0x55,0xD8,0x53,0x88,0x65,0x0E,0xC2,0xBE,0x4F,0x52,0xCD,0x8E,0x5A,0x29,0x4D,0xB9,0x59,0x1D,0x78,0x51,0x7C,0xB8,0x9B,0x98,0x4F,0xD1,0x73,0xAE,0x70,0x98,0x3E,0x4B,0x65,0x25,0x0E,0x42,0x48,0x17,0x0F,0xD4,0x35,0xCE,0x61,0xD9,0x75,0x78,0xA4,0x4E,0x18,0xC8,0xEC,0xA6,0x78,0xDC,0xEF,0xBF,0x6C,0xBE,0xF7,0x8B,0x14,0x3B,0x6C,0xC6,0x2E,0x75,0x30,0xC6,0x56,0xD1,0x28,0xBB,0x73,0x53,0x1B,0xB6,0x25,0xD1,0xAC,0xC4,0x64,0x7D,0x2E,0x1B,0x1C,0x63,0x47,0x97,0x66,0x92,0xEB,0x1C,0x04,0x29,0x33,0x43,0x1E,0x1A,0x15,0xB2,0x4F,0x1F,0xBB,0xA2,0x1A,0xBD,0xD4,0x47,0x78,0x9C,0xC7,0x7C,0x15,0x22,0xE6,0xC3,0x1A,0xCB,0xC0,0x1B,0x73,0xDA,0xAB,0xD0,0x59,0xE5,0xB2,0x85,0x4A,0x7D,0xAD,0x37,0x2F,0xD9,0x5C,0xED,0x75,0xFE,0xB8,0xDB,0x44,0x3F,0x05,0x68,0x78,0x4C,0xC2,0x63,0x34,0xDA,0x81,0x4D,0x23,0xEA,0x00,0x68,0x06,0x40,0x1A,0x87,0x01,0x99,0x02,0xC2,0x4F,0xC9,0x78,0xBF,0x73,0x04,0xD8,0xD7,0x49,0x15,0xD9,0x1A,0x0A,0xCD,0xFC,0x0A,0x02,0xFD,0x8B,0x40,0x0B,0xE0,0x16,0x69,0x52,0xB0,0x57,0xD0,0x04,0x17,0x49,0xC5,0x76,0x9F,0x2C,0xBB,0x1B,0x77,0x3E,0x29,0x3E,0x23,0xE4,0x74,0x3A,0x2D,0x77,0x4A,0x18,0xC0,0x7E,0x2B,0x11,0xCE,0xB8,0x7B,0x24,0x89,0x77,0x11,0x0A,0x15,0x42,0x63,0x39,0x7F,0xC9,0xD2,0x7E,0x72,0xCE,0x38,0x0D,0xBA,0x1B,0x79,0x4A,0xFA,0x4E,0xAC,0x0E,0xCB,0x3F,0x4A,0x4D,0x8D,0x37,0x64,0x39,0x3A,0x99,0x0F,0x79,0x71,0x12,0xC6,0x0B,0xD0,0x19,0x0B,0x6B,0x45,0x2E,0xCC,0x4B,0x95,0x2E,0x8A,0x05,0x28,0xD4,0x11,0x04,0xDE,0xB2,0xF7,0x23,0xA4,0x1A,0xC0,0x6F,0x6E,0xDC,0x65,0x50,0x32,0x52,0x6A,0x66,0xF6,0xAD,0xE5,0x76,0x53,0xA1,0x83,0x1B,0xD1,0x0E,0x1D,0x1C,0x6D,0x38,0x0C,0x18,0x39,0x9F,0x71,0x25,0x77,0x62,0x4C,0x36,0x56,0x57,0x0C,0x22};
int * keyPtr = (int*)m_TeaKey;
 
extern "C" void __declspec(dllexport) EncryptTCP(char* pBuf, const UINT uiSize)
{
	UINT uiEncodeSize = uiSize;

	// BLOCKÅ©±â °è»ê
	int iBlockCount = uiSize / 8;
	if (uiSize%8)
		iBlockCount++;

	// seed ¸ÂÃß±â
	//CMtRandom rand;
	//rand.srand( uiSize );

	UINT y, z, uiSum, uiLimit, uiRound;
	// round ¾ò±â
	//uiRound = (rand.rand()%2)+1;
	uiRound = (uiSize % 2) + 1;

	for (int i = 0; i<iBlockCount; i++)
	{

		UINT* pKey = (UINT*)m_TeaKey[uiSize%256];

		uiSum = 0;					//ÃÊ±âÈ­ 
		uiLimit = uiRound * 0x9E3779B9;

		// BLOCK ´ÜÀ§ encrypt
		if (uiEncodeSize >= 8)
		{
			memcpy(&y, pBuf + (i*8), sizeof(UINT));
			memcpy(&z, pBuf + ((i*8) + 4), sizeof(UINT));

			// start cycle
			while (uiSum != uiLimit)
			{
				y += (z << 4 ^ z >> 5) + z ^ uiSum + pKey[uiSum & 3];
				uiSum += 0x9E3779B9;
				z += (y << 4 ^ y >> 5) + y ^ uiSum + pKey[uiSum >> 11 & 3];
			}
			// end cycle

			memcpy(pBuf + (i*8), &y, sizeof(UINT));
			memcpy(pBuf + (i*8) + 4, &z, sizeof(UINT));

			uiEncodeSize -= 8;
		}
		// BYTE ´ÜÀ§ encrypt
		else //edge case for < 8 size.
		{
			char* pTempBuf = pBuf + (i*8);

			for (UINT j = 0; j<uiEncodeSize; ++j)
			{
				pTempBuf[j] ^= (reinterpret_cast<char*>(pKey))[j];
			}
		}
	}
}

extern "C" void __declspec(dllexport) DecryptTCP(char* pBuf, const UINT uiSize)
{
	UINT uiDecryptSize = uiSize;

	// BLOCKÅ©±â °è»ê
	int iBlockCount = uiSize / 8;
	if (uiSize%8)
		iBlockCount++;

	// seed ¸ÂÃß±â
	//CMtRandom rand;
	//rand.srand( uiSize );

	UINT y, z, uiSum, uiRound;
	// round ¾ò±â
	//uiRound = (rand.rand()%2)+1;
	uiRound = (uiSize % 2) + 1;

	for (int i = 0; i<iBlockCount; i++)
	{
		//UINT* pKey = s_TeaKey[rand.rand()%TEA_KEYCOUNT];
		UINT* pKey = (UINT*)m_TeaKey[uiSize%256];

		uiSum = uiRound * 0x9E3779B9;		// ÃÊ±âÈ­ 

		// BLOCK ´ÜÀ§ decrypt
		if (uiDecryptSize >= 8)
		{
			memcpy(&y, pBuf + (i*8), sizeof(UINT));
			memcpy(&z, pBuf + ((i*8) + 4), sizeof(UINT));

			// start cycle
			while (uiSum)
			{
				z -= (y << 4 ^ y >> 5) + y ^ uiSum + pKey[uiSum >> 11 & 3];
				uiSum -= 0x9E3779B9;
				y -= (z << 4 ^ z >> 5) + z ^ uiSum + pKey[uiSum & 3];
			}
			// end cycle

			memcpy(pBuf + (i*8), &y, sizeof(UINT));
			memcpy(pBuf + (i*8) + 4, &z, sizeof(UINT));

			uiDecryptSize -= 8;
		}
		// BYTE ´ÜÀ§ decrypt
		else
		{
			char* pTempBuf = pBuf + (i*8);

			for (UINT j = 0; j<uiDecryptSize; ++j)
			{
				pTempBuf[j] ^= (reinterpret_cast<char*>(pKey))[j];
			}
		}
	}
}

