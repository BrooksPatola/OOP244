#ifndef SICT_AMAPRODUCT_H__
#define SICT_AMAPRODUCT_H__
#include <iostream>
#include "ErrorMessage.h"
#include "Product.h"

namespace sict {

		class AmaProduct : public Product {
		private:
				//Holds a single character to tag the records as Perishable or non-Perishable product in a file.   
				char fileTag_;
				//Unit of Measurement
				char unit_[11];

		protected:
				ErrorMessage err_;

		public:
				AmaProduct(char = 'N');

				//Public member functions

				//returns a constant pointer to the unit_ member variable.
				//returning function from Header as did not work in CPP
				const char* unit()const;
			/*	Copies the incoming value string into the unit_ string.
				Make sure copying does not pass the size of the unit_ array.*/
				void unit(const char* value);

				std::fstream& store(std::fstream& file, bool addNewLine = true)const;
				std::fstream& load(std::fstream& file);
				std::ostream& write(std::ostream& os, bool linear)const;
				std::istream& read(std::istream& istr);
		};
}
#endif

