i2c_read_byte := $FEC6

SMC = $42
MOUSEDATA = $21

.import _mbut, _dx, _dy

.export _getmouse

.code
_getmouse:
  ldx #SMC
  ldy #MOUSEDATA
  jsr i2c_read_byte
  bcs die
  bit #$08
  beq nodata
  pha
  jsr i2c_read_byte
  bcs die1
  pha
  jsr i2c_read_byte
  bcs die2
  sta _dy
  pla
  sta _dx
  pla
  sta _mbut
  lda #1 ; return true (success)
  ldx #0
  rts
nodata:
  stz _dx
  stz _dy
  bra die
die2:
  pla
die1:
  pla
die:
  lda #0
  ldx #0
  rts
