#include <stdio.h>
#include <curl/curl.h>
 #include <iostream>
#include <string>
#include <stdlib.h>     /* malloc, free, rand */
#include <stdio.h>
#include <string.h>
 
 struct memory {
   char *response;
   size_t size;
 };


 static size_t cb_data(void *data, size_t size, size_t nmemb, void *userp)
 {
   printf("cb_data  %s\n", data);
    size_t realsize = size * nmemb;
  //  struct memory *mem = (struct memory *)userp;
 
  //  char *ptr = realloc(mem->response, mem->size + realsize + 1);
  //  if(ptr == NULL)
  //    return 0;  /* out of memory! */
  
  //  printf("cb  %s\n", data);

  //  mem->response = ptr;
  //  memcpy(&(mem->response[mem->size]), data, realsize);
  //  mem->size += realsize;
  //  mem->response[mem->size] = 0;
   
  return realsize;
 }
 


static size_t header_callback(char *buffer, size_t size,
                              size_t nitems, void *userdata)
{
  /* received header is nitems * size long in 'buffer' NOT ZERO TERMINATED */
  /* 'userdata' is set with CURLOPT_HEADERDATA */
  printf("header_callback  %s\n", buffer);
   
  return nitems * size;
}


int main(void)
{
  CURL *curl;
  CURLcode res;
 
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.ipify.org?format=json");

    //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);

      curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);


       struct memory chunk = {0};
 
 /* send all data to this function  */
 curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb_data);
 
 /* we pass our 'chunk' struct to the callback function */
 curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);



    res = curl_easy_perform(curl);
 
    if(CURLE_OK == res) {
      char *ct;
      /* ask for the content-type */
      res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);
 
      if((CURLE_OK == res) && ct){
         printf("\nWe received Content-Type: %s\n", ct);

      }
 
       

     
  
    }
 
    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  return 0;
}