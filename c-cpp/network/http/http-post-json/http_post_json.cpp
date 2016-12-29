struct my_string_t {
    char *ptr;
    size_t len;
};

void init_string(struct my_string_t *s) {
    s->len = 0;
    s->ptr = (char *)malloc(s->len + 1);
    if (s->ptr == NULL) {
        fprintf(stderr, "malloc() failed\n");
        exit(EXIT_FAILURE);
    }
    s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct my_string_t *s) {
    size_t new_len = s->len + size * nmemb;
    s->ptr = (char *)realloc(s->ptr, new_len + 1);
    if (s->ptr == NULL) {
        fprintf(stderr, "realloc() failed\n");
        exit(EXIT_FAILURE);
    }

    memcpy(s->ptr + s->len, ptr, size * nmemb);
    s->ptr[new_len] = '\0';
    s->len = new_len;

    return size * nmemb;
}

void http_post_json() {
    try {
        CURL *pCurl = nullptr;
        CURLcode res;

        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;

        // In windows, this will init the winsock stuff
        curl_global_init(CURL_GLOBAL_ALL);

        // get a curl handle
        pCurl = curl_easy_init();
        if (NULL != pCurl) {
            my_string_t http_response;
            init_string(&http_response);

            // 设置超时时间为1秒
            curl_easy_setopt(pCurl, CURLOPT_TIMEOUT, 5);

            // First set the URL that is about to receive our POST.
            // This URL can just as well be a
            // https:// URL if that is what should receive the data.
            curl_easy_setopt(pCurl, CURLOPT_URL,
                             "http://model.fuwo.com/model/octane/create_task/");

            // 设置http发送的内容类型为JSON
            // curl_slist *plist = curl_slist_append(NULL,
            //	"Content-Type:application/json;charset=UTF-8");
            // curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, plist);
            curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "no",
                         CURLFORM_COPYCONTENTS, params["no"].c_str(),
                         CURLFORM_END);

            curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "timestamp",
                         CURLFORM_COPYCONTENTS, params["timestamp"].c_str(),
                         CURLFORM_END);

            // curl_formadd(&formpost,
            //	&lastptr,
            //	CURLFORM_COPYNAME, "platform",
            //	CURLFORM_COPYCONTENTS, "10",
            //	CURLFORM_END);

            curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "sign",
                         CURLFORM_COPYCONTENTS, secret.c_str(), CURLFORM_END);

            // 设置要POST的JSON数据
            // curl_easy_setopt(pCurl, CURLOPT_POSTFIELDS, json_str_buf);
            curl_easy_setopt(pCurl, CURLOPT_HTTPPOST, formpost);
            curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, &http_response);
            curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, writefunc);

            // Perform the request, res will get the return code
            res = curl_easy_perform(pCurl);
            // Check for errors
            if (res != CURLE_OK) {
                printf("curl_easy_perform() failed:%s\n",
                       curl_easy_strerror(res));
            }
            // always cleanup
            curl_easy_cleanup(pCurl);
            curl_formfree(formpost);
            std::cout << http_response.ptr << std::endl;
            using json = nlohmann::json;
            auto jsonStructure = json::parse(http_response.ptr);
            std::cout << http_response.ptr << std::endl;
            if (jsonStructure["code"].get<std::string>() == "10000") {
                LOG(INFO) << "Inform succeed.";
                lua_pushboolean(L, true);
            } else {
                std::cout << "fuck error" << std::endl;
                lua_pushboolean(L, false);
            }
        }
        curl_global_cleanup();
    } catch (std::exception &ex) {
        printf("curl exception %s.\n", ex.what());
    }
}
