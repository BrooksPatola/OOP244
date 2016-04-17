#include "AmaPerishable.h"
#include <fstream>
#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;
namespace sict {

		AmaPerishable::AmaPerishable() : AmaProduct('P') {
		};


		const Date& AmaPerishable::expiry()const {
				return expiry_;
		}

		void AmaPerishable::expiry(const Date &value) {
				expiry_ = value;
		}

		std::fstream& AmaPerishable::store(std::fstream& file, bool addNewLine)const {

				AmaProduct::store(file, false);
				
				file << ',' << expiry_;
				if (addNewLine)
				{
						file << endl;
				}
				return file;

		}

		std::fstream& AmaPerishable::load(std::fstream& file) {

				AmaProduct::load(file);
				expiry_.read(file);
				file.ignore();

				return file;
		}

		std::ostream& AmaPerishable::write(std::ostream& ostr, bool linear)const {

				AmaProduct::write(ostr, linear);
				if (err_.isClear()) {
						if (linear) {
								ostr << expiry_;
						}
						else {
								ostr << endl << "Expiry date: " << expiry_;
						}
						

				}
				
				return ostr;

		}

		std::istream& AmaPerishable::read(std::istream& istr) {

        Date d;

				AmaProduct::read(istr);

				if (err_.isClear()) {
						cout << "Expiry date (YYYY/MM/DD): ";
						istr >> d;
				}
				if (d.bad()) {
						if (d.errCode() == CIN_FAILED) {
								err_.message("Invalid Date Entry");
						}
						else if (d.errCode() == YEAR_ERROR) {
								err_.message("Invalid Year in Date Entry");
						}
						else if (d.errCode() == MON_ERROR) {
								err_.message("Invalid Month in Date Entry");
						}
						else if (d.errCode() == DAY_ERROR) {
								err_.message("Invalid Day in Date Entry");
						}
						istr.setstate(ios::failbit);
				}
				else {
						(expiry(d));
				}
				return istr;
		}

}
		



