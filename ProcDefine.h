#ifndef _PROC_DEFINE_
#define _PROC_DEFINE_

#define PROC_BUFFER_MAX_SIZE 4096
#define PROC_BUFFER_MIN_SIZE 1024
#define PROC_BUFFER_PARAM_SIZE 1024
#define PROC_BUFFER_PARAMMIN_SIZE 512


#define TAG_RETOBJECT "#ret_object"
#define TAG_REQOBJECT "#request"
#define TAG_OBJECT	  "#object"
#define TAG_OUT		  "#out"

#define TAG_METHOD	  "#method"
#define TAG_PARAM     "#param"
#define TAG_RESULT    "#result"

#define DELIMITER_RESULT ":"

/*Proc parser define type code*/
#define PP_TYPE_ERROR 100
#define PP_TYPE_METHODCALL 0
#define PP_TYPE_REQOBJECT 1
#define PP_TYPE_RECEIVEOBJECT 2
#define PP_TYPE_RETOBJECT 3

#endif
