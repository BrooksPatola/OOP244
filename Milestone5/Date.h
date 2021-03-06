#ifndef SICT_DATE_H__
#define SICT_DATE_H__
#include <iostream>
namespace sict {
#define NO_ERROR 0
#define CIN_FAILED 1
#define YEAR_ERROR 2
#define MON_ERROR 3
#define DAY_ERROR 4


		class Date {
		private:
				int year_;
				int mon_;
				int day_;
				int readErrorCode_;
				void validate();
				void errCode(int);
				int value()const;
		public:
				Date();
				Date(int, int, int);

				bool operator==(const Date& D) const;
				bool operator!=(const Date& D) const;
				bool operator<(const Date& D) const;
				bool operator>(const Date& D) const;
				bool operator<=(const Date& D) const;
				bool operator>=(const Date& D) const;

				std::istream& read(std::istream& istr);
				std::ostream& write(std::ostream& ostr)const;




				int mdays()const;
				int errCode()const;
				bool bad()const;
		};


		std::ostream& operator<<(std::ostream& os, const Date& D);
		std::istream& operator>>(std::istream& is, Date& D);


}
#endif
