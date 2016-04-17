#include <iomanip>
#include <iostream>
using namespace std;
#include "Date.h"
#include "general.h"
namespace sict {
		int Date::value()const {
				return year_ * 372 + mon_ * 31 + day_;
		}
		int Date::mdays()const {
				int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
				int mon = mon_ >= 1 && mon_ <= 12 ? mon_ : 13;
				mon--;
				return days[mon] + int((mon == 1)*((year_ % 4 == 0) && (year_ % 100 != 0)) || (year_ % 400 == 0));
		}


		void Date::validate() {
				if (year_ < MIN_YEAR || year_ > MAX_YEAR) {
						readErrorCode_ = YEAR_ERROR;
				}
				else if (mon_ < 1 || mon_ > 12) {
						readErrorCode_ = MON_ERROR;
				}
				else if (day_ < 1 || day_ > mdays()) {
						readErrorCode_ = DAY_ERROR;
				}
				else {
						readErrorCode_ = NO_ERROR;
				}
		}

		void Date::errCode(int errorCode) {
				readErrorCode_ = errorCode;
		}


		Date::Date() {
				year_ = 0;
				mon_ = 0;
				day_ = 0;
				readErrorCode_ = NO_ERROR;
		}


		Date::Date(int y, int m, int d) {
				year_ = y;
				mon_ = m;
				day_ = d;
				readErrorCode_ = NO_ERROR;
		}

		int Date::errCode() const {
				return readErrorCode_;
		}

		bool Date::bad() const {
				return errCode() != NO_ERROR;
		}

		bool Date::operator==(const Date& D) const {
				return value() == D.value();
		}

		bool Date::operator!=(const Date& D) const {
				return value() != D.value();
		}

		bool Date::operator<(const Date& D) const {
				return value() < D.value();
		}

		bool Date::operator>(const Date& D) const {
				return value() > D.value();
		}

		bool Date::operator<=(const Date& D) const {
				return value() <= D.value();
		}

		bool Date::operator>=(const Date& D) const {
				return value() >= D.value();
		}

		std::istream& Date::read(std::istream& istr) {
				istr >> year_;
				if (istr.get() != '/') {
						readErrorCode_ = CIN_FAILED;
						return istr;
				}
				istr >> mon_;
				if (istr.get() != '/') {
						readErrorCode_ = CIN_FAILED;
						return istr;
				}
				istr >> day_;
				validate();
				return istr;
		}

		std::ostream& Date::write(std::ostream& ostr)const {
				ostr << year_ << "/";
				if (mon_ < 10) {
						ostr << "0";
				}
				ostr << mon_ << "/";
				if (day_ < 10) {
						ostr << "0";
				}
				ostr << day_;
				return ostr;
		}


		std::ostream& operator<<(std::ostream& os, const Date& D) {
				return D.write(os);
		}

		std::istream& operator>>(std::istream& is, Date& D) {
				return D.read(is);
		}





}
