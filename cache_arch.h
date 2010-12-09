/*
Core 2 Extreme QX6700: L1D: 32 KByte 8-way; L1I: 32 KByte; 2x4 MByte 16-way

Core 2 : L1D: 32 KByte 8-way; L1I: 32 KByte; 4/2 MByte 16-way

Athlon 64 X2 / FX-62: L1D: 64 KByte 2-way; L1I: 64 KByte; 2x 512 KByte / 2x 1 MByte (FX-62) 16-way

Pentium 4: L1D: 16 KByte 8-way; L1I: 12 Kuops (equivalent 8 till 16 KByte); 1 MByte 8-way


AMD PREFETCH and PREFETCHW
• K6-2:
• Small performance improvement – share FSB, low priority
• Don’t add overhead through useless prefetching
• K6-3:
• Separate backside bus
• Up to 20% improvements
Hagen Paul Pfeifer
3 | 19
• 64 bytes per prefetch
• AMD tip: prefetch 192 (3*64) bytes ahead or three cachelines (Prefetch
Distance)
• BTW: FSB and AMD is a separate topic (keyword HyperTransport,
Memory controller, Direct Connect Architecture )


-------------------
Pentium 3 has a 32-byte cacheline size, while a Core 2 has a 64-byte cacheline. 


 */
