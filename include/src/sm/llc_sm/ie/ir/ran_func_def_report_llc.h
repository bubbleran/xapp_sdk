#ifndef RAN_FUNC_DEF_REPORT_LLC_MIR_H
#define RAN_FUNC_DEF_REPORT_LLC_MIR_H 

// From 8.2.2.3
typedef struct{
  // Sequence of REPORT styles
  // [1 - 63]
  size_t sz_seq_report_sty;
  seq_report_sty_llc_t* seq_report_sty;

} ran_func_def_report_llc_t;

#endif
