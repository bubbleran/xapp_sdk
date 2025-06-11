/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef ANSWER_CJSON_MIR_H
#define ANSWER_CJSON_MIR_H 

#ifdef __cplusplus
extern "C" {
#endif


typedef struct{
  void const* it; 
  union{
  char* str;
  int val;
  float real;
  };
} ans_cjson_t;


#ifdef __cplusplus
}
#endif

#endif
