#pragma once
#include <IOperand.hpp>
#include <Exception.hpp>

typedef struct sOperandInfo {
	long min;
	long max;
	int precision;
} OperandInfo;

static OperandInfo operandInfoHolder[] = {
	{-128, 127, 0},                // INT_8
	{-32768, 32767, 0},            // INT16
	{-2147483648, 2147483647, 0},  // INT32
	{-32768, 32767, 6},            // FLOAT
	{-2147483648, 2147483647, 6}   // DOUBLE
};

template <typename T>
class Operand : public IOperand {
	public:
		Operand(eOperandType type, const double value) {
			_type = type;

			if (value < operandInfoHolder[type].min) {
				throw Exception("Underflow");
			} else if (value > operandInfoHolder[type].max) {
				throw Exception("Overflow");
			}

			switch (type) {
				case INT_8:
					_stringRep = std::to_string((int)value);
					break;
				case INT_16:
					_stringRep = std::to_string((int)value);
					break;
				case INT_32:
					_stringRep = std::to_string((int)value);
					break;
				case FLOAT:
					_stringRep = std::to_string((float)value);
				default:
					_stringRep = std::to_string(value);
			}

			_precision = operandInfoHolder[type].precision;
			_value = value;
		}
		~Operand(){};

		std::string const& toString() const { return _stringRep; };

		eOperandType getType() const { return _type; };

		int getPrecision() const { return _precision; };

		T getValue() const { return _value; };

		std::ostream &operator<<(std::ostream &os) {
			os << this->getValue();
			return (os);
		}

		IOperand const* operator+(IOperand const& rhs) const {
			eOperandType type = std::max(_type, rhs.getType());

			switch (type) {
				case INT_8:
					return new Operand<char>(type,
							_value + (char)std::stoi(rhs.toString()));
				case INT_16:
					return new Operand<int16_t>(
							type, _value + (int16_t)std::stoi(rhs.toString()));
				case INT_32:
					return new Operand<int32_t>(
							type, _value + (int32_t)std::stoi(rhs.toString()));
				case FLOAT:
					return new Operand<float>(type, _value + std::stof(rhs.toString()));
				case DOUBLE:
					return new Operand<double>(type, _value + std::stod(rhs.toString()));
			}
			return NULL;
		};

		IOperand const* operator-(IOperand const& rhs) const {
			eOperandType type = std::max(_type, rhs.getType());

			switch (type) {
				case INT_8:
					return new Operand<char>(type,
							_value - (char)std::stoi(rhs.toString()));
				case INT_16:
					return new Operand<int16_t>(
							type, _value - (int16_t)std::stoi(rhs.toString()));
				case INT_32:
					return new Operand<int32_t>(
							type, _value - (int32_t)std::stoi(rhs.toString()));
				case FLOAT:
					return new Operand<float>(type, _value - std::stof(rhs.toString()));
				case DOUBLE:
					return new Operand<double>(type, _value - std::stod(rhs.toString()));
			}
			return NULL;
		};

		IOperand const* operator*(IOperand const& rhs) const {
			eOperandType type = std::max(_type, rhs.getType());

			switch (type) {
				case INT_8:
					return new Operand<char>(type,
							_value * (char)std::stoi(rhs.toString()));
				case INT_16:
					return new Operand<int16_t>(
							type, _value * (int16_t)std::stoi(rhs.toString()));
				case INT_32:
					return new Operand<int32_t>(
							type, _value * (int32_t)std::stoi(rhs.toString()));
				case FLOAT:
					return new Operand<float>(type, _value * std::stof(rhs.toString()));
				case DOUBLE:
					return new Operand<double>(type, _value * std::stod(rhs.toString()));
			}
			return NULL;
		};
		IOperand const* operator/(IOperand const& rhs) const {
			eOperandType type = std::max(_type, rhs.getType());

			if (std::stod(rhs.toString()) == 0) {
				throw Exception("Division by zero");
			}

			switch (type) {
				case INT_8:
					return new Operand<char>(type,
							_value / (char)std::stoi(rhs.toString()));
				case INT_16:
					return new Operand<int16_t>(
							type, _value / (int16_t)std::stoi(rhs.toString()));
				case INT_32:
					return new Operand<int32_t>(
							type, _value / (int32_t)std::stoi(rhs.toString()));
				case FLOAT:
					return new Operand<float>(type, _value / std::stof(rhs.toString()));
				case DOUBLE:
					return new Operand<double>(type, _value / std::stod(rhs.toString()));
			}
			return NULL;
		};

		IOperand const* operator%(IOperand const& rhs) const {
			eOperandType type = std::max(_type, rhs.getType());

			if (type >= FLOAT) {
				throw Exception("Module with floating point value");
			}

			switch (type) {
				case INT_8:
					return new Operand<char>(type,
							(char)_value % (char)std::stoi(rhs.toString()));
				case INT_16:
					return new Operand<int16_t>(
							type, (int16_t)_value % (int16_t)std::stoi(rhs.toString()));
				case INT_32:
					return new Operand<int32_t>(
							type, (int32_t)_value % (int32_t)std::stoi(rhs.toString()));
				default:
					break;
			}
			return NULL;
		};

	private:
		eOperandType _type;
		T _value;
		int _precision;
		std::string _stringRep;
};
