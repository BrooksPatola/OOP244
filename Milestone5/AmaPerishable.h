#ifndef SICT_AMAPERISHABLE_H__
#define SICT_AMAPERISHABLE_H__
#include <iostream>
#include "ErrorMessage.h"
#include "Product.h"
#include "Date.h"
#include "AmaProduct.h"


namespace sict {
		class AmaPerishable :public AmaProduct {
		private:
				Date expiry_;

		public:
				AmaPerishable();
				//Public Accessors (setters and getters) 
				//returns a constant reference to expiry_ member variable. 
				const Date& expiry()const;
				//Sets the expiry_ attribute to the incoming value. 
				void expiry(const Date &value);
				// Virtual method implementations
				std::fstream& store(std::fstream& file, bool addNewLine = true)const;
				std::fstream& load(std::fstream& file);
				std::ostream& write(std::ostream& ostr, bool linear)const;
				std::istream& read(std::istream& istr);
		};
}
#endif
