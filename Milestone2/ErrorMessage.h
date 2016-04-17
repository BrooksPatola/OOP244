
#ifndef SICT_ERRORMESSAGE_H__
#define SICT_ERRORMESSAGE_H__
#include <iostream>
namespace sict {

		class ErrorMessage {

				char* message_;

		public:
				//constructors//
				ErrorMessage();
				ErrorMessage(const char* errorMessage);
				ErrorMessage(const ErrorMessage& em) = delete;

				//public member functions and operator overload//
				ErrorMessage& operator=(const ErrorMessage& em) = delete;
				ErrorMessage& operator=(const char* errorMessage);

				virtual ~ErrorMessage();
				void clear();
				bool isClear()const;
				void message(const char* value);
				const char* message()const;

		};


		std::ostream& operator<<(std::ostream& os, const ErrorMessage& M);
}
#endif

