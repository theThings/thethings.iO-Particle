#include "application.h"
#include "HttpClient/HttpClient.h"

/**
 * Declaring the variables.
 */
unsigned int nextTime = 0;    // Next time to contact the server
HttpClient http;
http_request_t request;
http_response_t response;

int cont = 0;

String msg ="{\"values\":[";

// Headers currently need to be set at init, useful for API keys etc.
http_header_t headers[] = {
		{ "Content-Type", "application/json" },
		{ "Accept" , "application/json" },
		{ NULL, NULL } // NOTE: Always terminate headers will NULL
};

//"{\"values\":[{\"key\":\"led\",\"value\":\"1\"}]}";
void addValue(String key, String value) {
		if (cont == 0) msg += "{\"key\":\""+key+"\",\"value\":\""+value+"\"}";
		else msg +=",{\"key\":\""+key+"\",\"value\":\""+value+"\"}";
		cont++;
}

void addValue(String key, int value) {
		if (cont == 0) msg += "{\"key\":\""+key+"\",\"value\":\""+value+"\"}";
		else msg += ",{\"key\":\""+key+"\",\"value\":\""+value+"\"}";
		cont++;
}

void addValue(String key, float value) {
		if (cont == 0) msg += "{\"key\":\""+key+"\",\"value\":\""+value+"\"}";
		else msg += ",{\"key\":\""+key+"\",\"value\":\""+value+"\"}";
		cont++;
}

void send() {
		msg += "]}";
		request.body = msg;
		http.post(request, response, headers);
		msg = "{\"values\":[";
		cont = 0;
}
void setup() {
		Serial.begin(9600);
		Serial.println();
		Serial.println("Application>\tStart of Loop.");
		// Request path and body can be set at runtime or at setup.
		request.hostname = "api.thethings.io";
		request.port = 80;
		request.path = "/v2/things/YOURTOKEN";
		addValue("Hello", "1");
		send();
}

void loop() {

}
