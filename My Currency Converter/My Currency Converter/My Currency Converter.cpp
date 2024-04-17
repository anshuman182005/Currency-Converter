#include <iostream>
#include <string>
#include <cpprest/http_client.h>

using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::client;

int main() {
	cout << "\t+-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-+" << endl; 
	cout << "\t          My Currency Converter        " << endl;
	cout << "\t+-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-+" << endl;
	string amount;
	string from;
	string to;
	cout << "\tEnter Amount : ";
	cin >> amount;
	cout << "\tFrom : ";
	cin >> from;
	cout << "\tTo : ";
	cin >> to;
	http_client client(U("https://api.apilayer.com/exchangerates_data"));
	uri_builder builder(U("/convert"));
	builder.append_query(U("to"), utility::conversions::to_string_t(to));
	builder.append_query(U("from"), utility::conversions::to_string_t(from));
	builder.append_query(U("amount"), utility::conversions::to_string_t(amount));
	builder.append_query(U("apikey"), U("NR2uhsYg3bkUYCIbA2pn126kwofHCGn5"));
	http_request request(methods::GET);
	request.set_request_uri(builder.to_string());
	client.request(request).then([](http_response response) {
		return response.extract_json();
	}).then([&](web::json::value body) {
		double result = body[U("info")][U("rate")].as_double()*stoi(amount);
		cout << "\tRate : " << result;
	}).wait();
	cout << " " << to;
	return 0;
}