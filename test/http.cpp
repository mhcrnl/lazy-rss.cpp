#include "gtest/gtest.h"

#include "http.hpp"

using namespace http;

TEST(HTTP, CheckOkResponse) {
    const int code = 200;
    const std::string reason = "Ok";
    const std::string body = "<html>test</html>";
    const std::string response_string = "HTTP Response(200, Ok)";

    auto body_copy = body; //Note that body is moved to avoid copy.

    auto response = HTTP_Response(code, reason, body_copy);

    EXPECT_EQ(response.status(), code);
    EXPECT_EQ(response.reason(), reason);
    EXPECT_EQ(response.body(), body);

    //200 is ok code so bool value should be true.
    EXPECT_TRUE(response);
    EXPECT_FALSE(!response);

    EXPECT_EQ(static_cast<std::string>(response), response_string);
}

TEST(HTTP, CheckErrorResponse) {
    const int code = 400;
    const std::string reason = "Bad Request";
    const std::string body = "<html>test</html>";
    const std::string response_string = "HTTP Response(400, Bad Request)";

    auto body_copy = body; //Note that body is moved to avoid copy.

    auto response = HTTP_Response(code, reason, body_copy);

    EXPECT_EQ(response.status(), code);
    EXPECT_EQ(response.reason(), reason);
    EXPECT_EQ(response.body(), body);

    EXPECT_TRUE(!response);
    EXPECT_FALSE(response);

    EXPECT_EQ(static_cast<std::string>(response), response_string);
}

TEST(HTTP, GetHttpRequestOk) {
    const int code = 200;
    const std::string reason = "OK";
    const char http_url[] = "http://httpbin.org/status/200";
    const char https_url[] = "https://httpbin.org/status/200";

    auto http_response = HTTP_Request(http_url).set_method(METHOD::GET).run();
    auto https_response = HTTPS_Request(https_url).set_method(METHOD::GET).run();

    ASSERT_EQ(http_response.status(), code);
    ASSERT_EQ(http_response.reason(), reason);
    ASSERT_EQ(https_response.status(), code);
    ASSERT_EQ(https_response.reason(), reason);
}

TEST(HTTP, GetHttpRequest400) {
    const int code = 400;
    const std::string reason = "BAD REQUEST";
    const char http_url[] = "http://httpbin.org/status/400";
    const char https_url[] = "https://httpbin.org/status/400";

    auto http_response = HTTP_Request(http_url).set_method(METHOD::GET).run();
    auto https_response = HTTPS_Request(https_url).set_method(METHOD::GET).run();

    ASSERT_EQ(http_response.status(), code);
    ASSERT_EQ(http_response.reason(), reason);
    ASSERT_EQ(https_response.status(), code);
    ASSERT_EQ(https_response.reason(), reason);
}
