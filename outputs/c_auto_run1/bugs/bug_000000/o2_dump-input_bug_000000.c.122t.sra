
;; Function testFunction (testFunction, funcdef_no=42, decl_uid=3234, cgraph_uid=43, symbol_order=42)

Created a replacement for s offset: 32, size: 8: s$buffer$0D.3354
Created a replacement for s offset: 40, size: 8: s$buffer$1D.3355
Created a replacement for s offset: 48, size: 8: s$buffer$2D.3356
Created a replacement for s offset: 56, size: 8: s$buffer$3D.3357
Created a replacement for s offset: 0, size: 32: s$dataD.3358
Created a replacement for D.3352 offset: 0, size: 32: SR.25D.3359
Created a replacement for D.3352 offset: 32, size: 8: SR.26D.3360
Created a replacement for D.3352 offset: 40, size: 8: SR.27D.3361
Created a replacement for D.3352 offset: 48, size: 8: SR.28D.3362
Created a replacement for D.3352 offset: 56, size: 8: SR.29D.3363

Symbols to be put in SSA form
{ D.3294 D.3354 D.3355 D.3356 D.3357 D.3358 D.3359 D.3360 D.3361 D.3362 D.3363 }
Incremental SSA update started at block: 0
Number of blocks in CFG: 6
Number of blocks to update: 5 ( 83%)


__attribute__((access ("^1[ ]", )))
void testFunction (int32_t x, uint8_t * y)
{
  const unsigned char SR.29;
  const unsigned char SR.28;
  const unsigned char SR.27;
  const unsigned char SR.26;
  int SR.25;
  int s$data;
  const unsigned char s$buffer$3;
  const unsigned char s$buffer$2;
  const unsigned char s$buffer$1;
  const unsigned char s$buffer$0;
  struct MyStruct D.3352;
  struct MyStruct s;
  int i;
  const int s$data;
  uint32_t h;
  int i;
  struct MyStruct s;
  sizetype _18;
  const uint8_t * _19;
  unsigned char _20;
  unsigned char _29;
  unsigned int _30;
  unsigned char _35;
  unsigned int _36;
  unsigned char _41;
  unsigned int _42;
  unsigned char _47;
  unsigned int _48;

  <bb 2> [local count: 214748368]:
  MEM <char[4]> [(struct  *)&s + 4B] = {};

  <bb 3> [local count: 858993457]:
  # i_44 = PHI <i_21(5), 0(2)>
  _18 = (sizetype) i_44;
  _19 = &y + _18;
  _20 = *_19;
  s.buffer[i_44] = _20;
  i_21 = i_44 + 1;
  if (i_21 != 4)
    goto <bb 5>; [75.00%]
  else
    goto <bb 4>; [25.00%]

  <bb 5> [local count: 644245086]:
  goto <bb 3>; [100.00%]

  <bb 4> [local count: 214748368]:
  s$data_22 = x_2(D);
  s.data = s$data_22;
  D.3352 = s;
  SR.25_38 = s$data_22;
  SR.26_32 = MEM <const uint8_t> [(struct  *)&s + 4B];
  SR.27_12 = MEM <const uint8_t> [(struct  *)&s + 5B];
  SR.28_6 = MEM <const uint8_t> [(struct  *)&s + 6B];
  SR.29_9 = MEM <const uint8_t> [(struct  *)&s + 7B];
  s ={v} {CLOBBER};
  MEM <int32_t> [(struct  *)&s] = SR.25_38;
  MEM <const uint8_t> [(struct  *)&s + 4B] = SR.26_32;
  MEM <const uint8_t> [(struct  *)&s + 5B] = SR.27_12;
  MEM <const uint8_t> [(struct  *)&s + 6B] = SR.28_6;
  MEM <const uint8_t> [(struct  *)&s + 7B] = SR.29_9;
  s$buffer$0_3 = SR.26_32;
  s$buffer$1_13 = SR.27_12;
  s$buffer$2_7 = SR.28_6;
  s$buffer$3_8 = SR.29_9;
  __printf_chk (1, "%d\n", x_2(D));
  h_5 = (uint32_t) x_2(D);
  _29 = s$buffer$0_3;
  _30 = (unsigned int) _29;
  h_31 = h_5 + _30;
  _35 = s$buffer$1_13;
  _36 = (unsigned int) _35;
  h_37 = h_31 + _36;
  _41 = s$buffer$2_7;
  _42 = (unsigned int) _41;
  h_43 = h_37 + _42;
  _47 = s$buffer$3_8;
  _48 = (unsigned int) _47;
  h_49 = h_43 + _48;
  __printf_chk (1, "%u\n", h_49);
  s ={v} {CLOBBER};
  return;

}



;; Function createStruct (createStruct, funcdef_no=39, decl_uid=3212, cgraph_uid=40, symbol_order=39)

Created a replacement for s offset: 0, size: 32: s$dataD.3377

Symbols to be put in SSA form
{ D.3291 D.3377 }
Incremental SSA update started at block: 0
Number of blocks in CFG: 6
Number of blocks to update: 5 ( 83%)


__attribute__((access ("^1[ ]", )))
struct MyStruct createStruct (int32_t val, const uint8_t * arr)
{
  int s$data;
  int i;
  struct MyStruct s;
  struct MyStruct D.3281;
  sizetype _1;
  const uint8_t * _2;
  unsigned char _3;

  <bb 2> [local count: 214748368]:
  MEM <char[4]> [(struct  *)&s + 4B] = {};

  <bb 3> [local count: 858993457]:
  # i_18 = PHI <i_13(5), 0(2)>
  _1 = (sizetype) i_18;
  _2 = arr_11(D) + _1;
  _3 = *_2;
  s.buffer[i_18] = _3;
  i_13 = i_18 + 1;
  if (i_13 != 4)
    goto <bb 5>; [75.00%]
  else
    goto <bb 4>; [25.00%]

  <bb 5> [local count: 644245086]:
  goto <bb 3>; [100.00%]

  <bb 4> [local count: 214748368]:
  s$data_5 = val_8(D);
  s.data = s$data_5;
  D.3281 = s;
  s ={v} {CLOBBER};
  return D.3281;

}



;; Function printStruct (printStruct, funcdef_no=40, decl_uid=3221, cgraph_uid=41, symbol_order=40)

void printStruct (const struct MyStruct * s)
{
  int _1;

  <bb 2> [local count: 1073741824]:
  _1 = s_3(D)->data;
  __printf_chk (1, "%d\n", _1);
  return;

}



;; Function hashStruct (hashStruct, funcdef_no=41, decl_uid=3224, cgraph_uid=42, symbol_order=41)

uint32_t hashStruct (const struct MyStruct * s)
{
  int i;
  uint32_t h;
  int _1;
  unsigned char _13;
  unsigned int _14;
  unsigned char _19;
  unsigned int _20;
  unsigned char _25;
  unsigned int _26;
  unsigned char _31;
  unsigned int _32;

  <bb 2> [local count: 214748368]:
  _1 = s_7(D)->data;
  h_8 = (uint32_t) _1;
  _13 = s_7(D)->buffer[0];
  _14 = (unsigned int) _13;
  h_15 = h_8 + _14;
  _19 = s_7(D)->buffer[1];
  _20 = (unsigned int) _19;
  h_21 = h_15 + _20;
  _25 = s_7(D)->buffer[2];
  _26 = (unsigned int) _25;
  h_27 = h_21 + _26;
  _31 = s_7(D)->buffer[3];
  _32 = (unsigned int) _31;
  h_33 = h_27 + _32;
  return h_33;

}



;; Function runTests (runTests, funcdef_no=43, decl_uid=3238, cgraph_uid=44, symbol_order=43)

void runTests (void (*TestFunc) (int32_t, uint8_t *) func)
{
  int i;
  uint8_t arr[4][4];
  int32_t vals[4];
  uint8_t[4] * _1;
  int _2;

  <bb 2> [local count: 214748368]:
  vals[0] = 10;
  vals[1] = -10;
  vals[2] = -2147483648;
  vals[3] = 2147483647;
  arr[0] = "\x00";
  arr[1] = "\x01\x02\x03\x04";
  arr[2] = "\x05\x06\x07\b";
  arr[3] = "\t\n\v\f";

  <bb 3> [local count: 858993457]:
  # i_21 = PHI <i_19(3), 0(2)>
  _1 = &arr[i_21];
  _2 = vals[i_21];
  func_17(D) (_2, _1);
  i_19 = i_21 + 1;
  if (i_19 != 4)
    goto <bb 3>; [80.00%]
  else
    goto <bb 4>; [20.00%]

  <bb 4> [local count: 214748368]:
  vals ={v} {CLOBBER};
  arr ={v} {CLOBBER};
  return;

}



;; Function complexFunction (complexFunction, funcdef_no=44, decl_uid=3247, cgraph_uid=45, symbol_order=44)

Created a replacement for s offset: 32, size: 8: s$buffer$0D.3421
Created a replacement for s offset: 40, size: 8: s$buffer$1D.3422
Created a replacement for s offset: 48, size: 8: s$buffer$2D.3423
Created a replacement for s offset: 56, size: 8: s$buffer$3D.3424
Created a replacement for s offset: 0, size: 32: s$dataD.3425
Created a replacement for D.3417 offset: 0, size: 32: SR.75D.3426
Created a replacement for D.3417 offset: 32, size: 8: SR.76D.3427
Created a replacement for D.3417 offset: 40, size: 8: SR.77D.3428
Created a replacement for D.3417 offset: 48, size: 8: SR.78D.3429
Created a replacement for D.3417 offset: 56, size: 8: SR.79D.3430

Symbols to be put in SSA form
{ D.3296 D.3421 D.3422 D.3423 D.3424 D.3425 D.3426 D.3427 D.3428 D.3429 D.3430 }
Incremental SSA update started at block: 0
Number of blocks in CFG: 7
Number of blocks to update: 6 ( 86%)


void complexFunction ()
{
  const unsigned char SR.79;
  const unsigned char SR.78;
  const unsigned char SR.77;
  const unsigned char SR.76;
  int SR.75;
  int s$data;
  const unsigned char s$buffer$3;
  const unsigned char s$buffer$2;
  const unsigned char s$buffer$1;
  const unsigned char s$buffer$0;
  int i;
  struct MyStruct s;
  struct MyStruct D.3417;
  const int s$data;
  uint32_t h;
  int i;
  struct MyStruct s;
  int i;
  uint8_t arr[4][4];
  int32_t vals[4];
  uint8_t[4] * _1;
  int _2;
  sizetype _33;
  const uint8_t * _34;
  unsigned char _35;
  unsigned char _44;
  unsigned int _45;
  unsigned char _50;
  unsigned int _51;
  unsigned char _56;
  unsigned int _57;
  unsigned char _62;
  unsigned int _63;

  <bb 2> [local count: 53687093]:
  vals[0] = 10;
  vals[1] = -10;
  vals[2] = -2147483648;
  vals[3] = 2147483647;
  arr[0] = "\x00";
  arr[1] = "\x01\x02\x03\x04";
  arr[2] = "\x05\x06\x07\b";
  arr[3] = "\t\n\v\f";

  <bb 3> [local count: 214748368]:
  # i_32 = PHI <i_20(5), 0(2)>
  _1 = &arr[i_32];
  _2 = vals[i_32];
  MEM <char[4]> [(struct  *)&s + 4B] = {};

  <bb 4> [local count: 858993457]:
  # i_26 = PHI <i_36(4), 0(3)>
  _33 = (sizetype) i_26;
  _34 = _1 + _33;
  _35 = *_34;
  s.buffer[i_26] = _35;
  i_36 = i_26 + 1;
  if (i_36 != 4)
    goto <bb 4>; [75.00%]
  else
    goto <bb 5>; [25.00%]

  <bb 5> [local count: 214748368]:
  s$data_5 = _2;
  s.data = s$data_5;
  D.3417 = s;
  SR.75_37 = s$data_5;
  SR.76_3 = MEM <const uint8_t> [(struct  *)&s + 4B];
  SR.77_22 = MEM <const uint8_t> [(struct  *)&s + 5B];
  SR.78_25 = MEM <const uint8_t> [(struct  *)&s + 6B];
  SR.79_15 = MEM <const uint8_t> [(struct  *)&s + 7B];
  s ={v} {CLOBBER};
  MEM <int32_t> [(struct  *)&s] = SR.75_37;
  MEM <const uint8_t> [(struct  *)&s + 4B] = SR.76_3;
  MEM <const uint8_t> [(struct  *)&s + 5B] = SR.77_22;
  MEM <const uint8_t> [(struct  *)&s + 6B] = SR.78_25;
  MEM <const uint8_t> [(struct  *)&s + 7B] = SR.79_15;
  s$buffer$0_54 = SR.76_3;
  s$buffer$1_55 = SR.77_22;
  s$buffer$2_59 = SR.78_25;
  s$buffer$3_60 = SR.79_15;
  __printf_chk (1, "%d\n", _2);
  h_21 = (uint32_t) _2;
  _44 = s$buffer$0_54;
  _45 = (unsigned int) _44;
  h_46 = h_21 + _45;
  _50 = s$buffer$1_55;
  _51 = (unsigned int) _50;
  h_52 = h_46 + _51;
  _56 = s$buffer$2_59;
  _57 = (unsigned int) _56;
  h_58 = h_52 + _57;
  _62 = s$buffer$3_60;
  _63 = (unsigned int) _62;
  h_64 = h_58 + _63;
  __printf_chk (1, "%u\n", h_64);
  s ={v} {CLOBBER};
  i_20 = i_32 + 1;
  if (i_20 != 4)
    goto <bb 3>; [80.00%]
  else
    goto <bb 6>; [20.00%]

  <bb 6> [local count: 53687093]:
  vals ={v} {CLOBBER};
  arr ={v} {CLOBBER};
  return;

}



;; Function complexMacroTest (complexMacroTest, funcdef_no=49, decl_uid=3257, cgraph_uid=46, symbol_order=45)

void complexMacroTest ()
{
  <bb 2> [local count: 53687093]:
  complexFunction (); [tail call]
  return;

}



;; Function runComplexTests (runComplexTests, funcdef_no=51, decl_uid=3268, cgraph_uid=47, symbol_order=46)

void runComplexTests ()
{
  <bb 2> [local count: 53687093]:
  complexFunction (); [tail call]
  return;

}



;; Function main (main, funcdef_no=47, decl_uid=3278, cgraph_uid=48, symbol_order=47) (executed once)

int main ()
{
  <bb 2> [local count: 1073741824]:
  runTests (testFunction);
  complexFunction ();
  complexFunction ();
  complexFunction ();
  return 0;

}


