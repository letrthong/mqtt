#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <iostream>
#include <string>


 // https://curl.se/libcurl/c/CURLOPT_HTTPHEADER.html
// https://curl.se/libcurl/c/curl_easy_getinfo.html

int main(void)
{
  CURL *curl;
  CURLcode res;
 
  static const char *postthis = "moo mooo moo moo";
 
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://example.com");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postthis);
 
    /* if we do not provide POSTFIELDSIZE, libcurl will strlen() by
       itself */
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
 
    
    res = curl_easy_perform(curl);

     
    /* Check for errors */
    if(res != CURLE_OK){
         fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    }else{
        long response_code;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        printf("response_code =%d\n", response_code);


        char *ct;
        /* ask for the content-type */
        res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);

        if((CURLE_OK == res) && ct){
            printf("We received Content-Type: %s\n", ct);
        }
        
    }
     
            
     
    
    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  return 0;
}