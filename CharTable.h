/////////////////////////////////////////////////////////////////////////////////////////////////////////
//custom made 3x5 font.
//should comment out all uneeded values and adjust the entrypoint of 31? in the main loop

const char CH_3x5[] PROGMEM = { ////////////////////////////////////Standard Table *do not append. mod of cha
	//width, height, 5 columns (bottom-to-top)
	0x00, 0x00, 0x00, // space
	0x0, 0x17, 0x0, //Char: !
	0x3, 0x0, 0x3, //Char: "
	0x1F, 0xA, 0x1F, //Char: #
	0x16, 0x1F, 0xD, //Char: $
	0x9, 0x4, 0x12, //Char: %
	0xA, 0x15, 0x1A, //Char: &
	0x3, 0x0, 0x0, //Char: '
	0xE, 0x11, 0x0, //Char: (
	0x0, 0x11, 0xE, //Char: )
	0x3, 0x3, 0x0, //Char: *
	0x4, 0xE, 0x4, //Char: +
	0x10, 0x8, 0x0, //Char: ,
	0x4, 0x4, 0x4, //Char: -
	0x0, 0x0, 0x10, //Char: .
	0x10, 0x8, 0x4, //Char: /
	0x1F, 0x11, 0x1F, //Char: 0
	0x2, 0x1F, 0x0, //Char: 1
	0x19, 0x15, 0x13, //Char: 2
	0x15, 0x15, 0x1B, //Char: 3
	0x7, 0x4, 0x1F, //Char: 4
	0x17, 0x15, 0x1D, //Char: 5
	0x1F, 0x14, 0x1C, //Char: 6
	0x1, 0x1, 0x1F, //Char: 7
	0x1F, 0x15, 0x1F, //Char: 8
	0x7, 0x5, 0x1F, //Char: 9
	0x0, 0xA, 0x0, //Char: :
	0x10, 0xA, 0x0, //Char: ;
	0x4, 0xA, 0x11, //Char: <
	0xA, 0xA, 0xA, //Char: =
	0x11, 0xA, 0x4, //Char: >
	0x2, 0x19, 0x6, //Char: ?
	0x1D, 0x15, 0x1D, //Char: @
	0x1E, 0x5, 0x1E, // A
	0x1F, 0x15, 0xA, // B
	0x1F, 0x11, 0x11, //Char:C
	0x1F, 0x11, 0xE, //Char: D
	0x1F, 0x15, 0x15, //Char: E
	0x1F, 0x5, 0x5, //Char: F
	0x1F, 0x11, 0x19, //Char: G
	0x1F, 0x4, 0x1F, //Char: H
	0x11, 0x1F, 0x11, //Char: I
	0x8, 0x10, 0xF, //Char: J
	0x1F, 0x4, 0x1B, //Char: K
	0x1F, 0x10, 0x10, //Char: L
	0x1F, 0x4, 0x1F, //Char: M
	0x1F, 0x4, 0x1F, //Char: N
	0x1F, 0x11, 0x1F, //Char: O
	0x1F, 0x5, 0x7, //Char: P
	0x1F, 0x11, 0xF, //Char: Q
	0x1F, 0x5, 0x1B, //Char: R
	0x17, 0x15, 0x1D, //Char: S
	0x1, 0x1F, 0x1, //Char: T
	0x1F, 0x10, 0x1F, //Char: U
	0xF, 0x10, 0xF, //Char: V
	0xF, 0x10, 0xF, //Char: W
	0x1B, 0x4, 0x1B, //Char: X
	0x3, 0x1C, 0x3, //Char: Y
	0x19, 0x15, 0x13,  //Char: Z
	0x0, 0x1F, 0x11, //Char: [ //dont really need any after 'Z' Plus Im not sure any of them are mapped to a font layout
	0x3, 0x4, 0x18, //Char: '\'
	0x11, 0x1F, 0x0, //Char: ]
	0x2, 0x1, 0x2, //Char: hat
	0x10, 0x10, 0x10, //Char: _
	0x1, 0x2, 0x0, //Char: `
	0xC, 0x12, 0x1C, //Char: a
	0x1F, 0x12, 0xC, //Char: b
	0xC, 0x12, 0x12, //Char: c
	0xC, 0x12, 0x1F, //Char: d
	0xC, 0x1A, 0x14, //Char: e
	0x4, 0x1F, 0x5, //Char: f
	0x14, 0x1A, 0xC, //Char: g
	0x1F, 0x4, 0x18, //Char: h
	0x0, 0x1D, 0x0, //Char: i
	0x10, 0xD, 0x0, //Char: j
	0x1F, 0x8, 0x14, //Char: k
	0x0, 0x1F, 0x0, //Char: l
	0x1F, 0x3, 0x1F, //Char: m
	0x1C, 0x2, 0x1C, //Char: n
	0xC, 0x12, 0xC, //Char: o
	0x1E, 0xA, 0x4, //Char: p
	0x4, 0xA, 0x1E, //Char: q
	0x0, 0x1E, 0x4, //Char: r
	0x14, 0xA, 0x0, //Char: s
	0x2, 0x1F, 0x2, //Char: t
	0xE, 0x10, 0xE, //Char: u
	0x6, 0x18, 0x6, //Char: v
	0xE, 0x18, 0xE, //Char: w
	0x12, 0xC, 0x12, //Char: x
	0x16, 0x18, 0xE, //Char: y
	0x1A, 0x1E, 0x16, //Char: z
	0x4, 0xE, 0x11, //Char: {
	0x0, 0x1F, 0x0, //Char: |
	0x11, 0xE, 0x4, //Char: }
	0x2, 0x6, 0x4, //Char: ~
};


//////////////////////////////////////////////////////////////////////////////////////////////////////|


const char CH_8x8[] PROGMEM =  {
	0,0,0,0,0,0,0,0, // SPACE
	0x10,0x18,0x18,0x18,0x18,0x00,0x18,0x18, // !
	0x28,0x28,0x08,0x00,0x00,0x00,0x00,0x00, // QUOT
	0x00,0x0a,0x7f,0x14,0x28,0xfe,0x50,0x00, // #
	0x10,0x38,0x54,0x70,0x1c,0x54,0x38,0x10, // $
	0x00,0x60,0x66,0x08,0x10,0x66,0x06,0x00, // %
	0,0,0,0,0,0,0,0, // &
	0x00,0x10,0x18,0x18,0x08,0x00,0x00,0x00, // '
	0x02,0x04,0x08,0x08,0x08,0x08,0x08,0x04, // (
	0x40,0x20,0x10,0x10,0x10,0x10,0x10,0x20, // )
	0x00,0x10,0x54,0x38,0x10,0x38,0x54,0x10, // *
	0x00,0x08,0x08,0x08,0x7f,0x08,0x08,0x08, // +
	0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x08, // ,
	0x00,0x00,0x00,0x00,0x7e,0x00,0x00,0x00, // -
	0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06, // .
	0x00,0x04,0x04,0x08,0x10,0x20,0x40,0x40, // /
	0x00,0x38,0x44,0x4c,0x54,0x64,0x44,0x38, // 0
	0x04,0x0c,0x14,0x24,0x04,0x04,0x04,0x04, // 1
	0x00,0x30,0x48,0x04,0x04,0x38,0x40,0x7c, // 2
	0x00,0x38,0x04,0x04,0x18,0x04,0x44,0x38, // 3
	0x00,0x04,0x0c,0x14,0x24,0x7e,0x04,0x04, // 4
	0x00,0x7c,0x40,0x40,0x78,0x04,0x04,0x38, // 5
	0x00,0x38,0x40,0x40,0x78,0x44,0x44,0x38, // 6
	0x00,0x7c,0x04,0x04,0x08,0x08,0x10,0x10, // 7
	0x00,0x3c,0x44,0x44,0x38,0x44,0x44,0x78, // 8
	0x00,0x38,0x44,0x44,0x3c,0x04,0x04,0x78, // 9
	0x00,0x18,0x18,0x00,0x00,0x18,0x18,0x00, // :
	0x00,0x18,0x18,0x00,0x00,0x18,0x18,0x08, // ;
	0x00,0x10,0x20,0x40,0x80,0x40,0x20,0x10, // <
	0x00,0x00,0x7e,0x00,0x00,0xfc,0x00,0x00, // =
	0x00,0x08,0x04,0x02,0x01,0x02,0x04,0x08, // >
	0x00,0x38,0x44,0x04,0x08,0x10,0x00,0x10, // ?
	0x00,0x30,0x48,0xba,0xba,0x84,0x78,0x00, // @
	0x00,0x1c,0x22,0x42,0x42,0x7e,0x42,0x42, // A
	0x00,0x78,0x44,0x44,0x78,0x44,0x44,0x7c, // B
	0x00,0x3c,0x44,0x40,0x40,0x40,0x44,0x7c, // C
	0x00,0x7c,0x42,0x42,0x42,0x42,0x44,0x78, // D
	0x00,0x78,0x40,0x40,0x70,0x40,0x40,0x7c, // E
	0x00,0x7c,0x40,0x40,0x78,0x40,0x40,0x40, // F
	0x00,0x3c,0x40,0x40,0x5c,0x44,0x44,0x78, // G
	0x00,0x42,0x42,0x42,0x7e,0x42,0x42,0x42, // H
	0x00,0x7c,0x10,0x10,0x10,0x10,0x10,0x7e, // I
	0x00,0x7e,0x02,0x02,0x02,0x02,0x04,0x38, // J
	0x00,0x44,0x48,0x50,0x60,0x50,0x48,0x44, // K
	0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x7c, // L
	0x00,0x82,0xc6,0xaa,0x92,0x82,0x82,0x82, // M
	0x00,0x42,0x42,0x62,0x52,0x4a,0x46,0x42, // N
	0x00,0x3c,0x42,0x42,0x42,0x42,0x44,0x38, // O
	0x00,0x78,0x44,0x44,0x48,0x70,0x40,0x40, // P
	0x00,0x3c,0x42,0x42,0x52,0x4a,0x44,0x3a, // Q
	0x00,0x78,0x44,0x44,0x78,0x50,0x48,0x44, // R
	0x00,0x38,0x40,0x40,0x38,0x04,0x04,0x78, // S
	0x00,0x7e,0x90,0x10,0x10,0x10,0x10,0x10, // T
	0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x3e, // U
	0x00,0x42,0x42,0x42,0x42,0x44,0x28,0x10, // V
	0x80,0x82,0x82,0x92,0x92,0x92,0x94,0x78, // W
	0x00,0x42,0x42,0x24,0x18,0x24,0x42,0x42, // X
	0x00,0x44,0x44,0x28,0x10,0x10,0x10,0x10, // Y
	0x00,0x7c,0x04,0x08,0x7c,0x20,0x40,0xfe, // Z
};