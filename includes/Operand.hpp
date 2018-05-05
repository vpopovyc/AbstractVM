/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 17:07:42 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/05/01 17:07:44 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <tuple>
#include <cmath>
#include <cfloat>
#include <cstdint>
#include <IOperand.hpp>
#include <AVMException.hpp>

namespace OperandFactory{
template <typename T> IOperand const *createOperand(OperandType type, T const &value);	
}

template <typename T>
class Operand : public IOperand
{
public:
	~Operand() {};
	Operand(const Operand &rhs) { *this = rhs; } 
	Operand &operator=(const Operand &rhs) { m_data = rhs.m_data; m_type = rhs.m_type; m_str = rhs.m_str; return *this; } 

	Operand(const T &data, const OperandType &type) : m_data(data), m_type(type), m_str(std::to_string(data)) {};

	T getData() const { return m_data; }
	int getPrecision(void) const { return static_cast<int>(m_type); }
	OperandType getType(void) const { return m_type; }

	std::string const &toString(void) const { return m_str; }

	bool operator==(IOperand const &rhs) const
	{
		auto compare = [&](auto *op) -> bool {
			return (getData() == op->getData());
		};

		auto *op1 = dynamic_cast<const Operand<int8_t> *>(&rhs);
		if (op1) {
			return compare(op1);
		}
		auto *op2 = dynamic_cast<const Operand<int16_t> *>(&rhs);
		if (op2) {
			return compare(op2);
		}
		auto *op3 = dynamic_cast<const Operand<int32_t> *>(&rhs);
		if (op3) {
			return compare(op3);
		}
		auto *op4 = dynamic_cast<const Operand<float> *>(&rhs);
		if (op4) {
			return compare(op4);
		}
		auto *op5 = dynamic_cast<const Operand<double> *>(&rhs);
		if (op5) {
			return compare(op5);
		}
		throw AVMException(Reason::UNKNOWN_OPERAND, "Comparison of unknown operand");
	}

	IOperand const *operator+(IOperand const &rhs) const
	{
		auto plus = [&](auto *op) -> IOperand const * {
			OperandType type = this->getPrecision() >= op->getPrecision() ? 
							   this->getType() : op->getType();

			auto eval = std::bind([&](OperandType type, auto value) { return runtimeEvaluationOf(type, value); },
								  type, std::placeholders::_1);

			if (type == OperandType::FLOAT || type == OperandType::DOUBLE) {
				long double value = (long double)getData() + (long double)op->getData();
				return eval(value);
			} else {
				ssize_t value = (ssize_t)getData() + (ssize_t)op->getData();
				return eval(value);
			}
		};

		auto *op1 = dynamic_cast<const Operand<int8_t> *>(&rhs);
		if (op1) {
			return plus(op1);
		}
		auto *op2 = dynamic_cast<const Operand<int16_t> *>(&rhs);
		if (op2) {
			return plus(op2);
		}
		auto *op3 = dynamic_cast<const Operand<int32_t> *>(&rhs);
		if (op3) {
			return plus(op3);
		}
		auto *op4 = dynamic_cast<const Operand<float> *>(&rhs);
		if (op4) {
			return plus(op4);
		}
		auto *op5 = dynamic_cast<const Operand<double> *>(&rhs);
		if (op5) {
			return plus(op5);
		}
		throw AVMException(Reason::UNKNOWN_OPERAND, "Addition of unknown operand");
	}

	IOperand const *operator-(IOperand const &rhs) const
	{
		auto minus = [&](auto *op) -> IOperand const * {
			OperandType type = this->getPrecision() >= op->getPrecision() ? 
							   this->getType() : op->getType();

			auto eval = std::bind([&](OperandType type, auto value) { return runtimeEvaluationOf(type, value); },
								  type, std::placeholders::_1);

			if (type == OperandType::FLOAT || type == OperandType::DOUBLE) {
				long double value = (long double)getData() - (long double)op->getData();
				return eval(value);
			} else {
				ssize_t value = (ssize_t)getData() - (ssize_t)op->getData();
				return eval(value);
			}
		};

		auto *op1 = dynamic_cast<const Operand<int8_t> *>(&rhs);
		if (op1) {
			return minus(op1);
		}
		auto *op2 = dynamic_cast<const Operand<int16_t> *>(&rhs);
		if (op2) {
			return minus(op2);
		}
		auto *op3 = dynamic_cast<const Operand<int32_t> *>(&rhs);
		if (op3) {
			return minus(op3);
		}
		auto *op4 = dynamic_cast<const Operand<float> *>(&rhs);
		if (op4) {
			return minus(op4);
		}
		auto *op5 = dynamic_cast<const Operand<double> *>(&rhs);
		if (op5) {
			return minus(op5);
		}
		throw AVMException(Reason::UNKNOWN_OPERAND, "Substraction of unknown operand");
	}

	IOperand const *operator*(IOperand const &rhs) const
	{
		auto mul = [&](auto *op) -> IOperand const * {
			OperandType type = this->getPrecision() >= op->getPrecision() ? 
							   this->getType() : op->getType();

			auto eval = std::bind([&](OperandType type, auto value) { return runtimeEvaluationOf(type, value); },
								  type, std::placeholders::_1);

			if (type == OperandType::FLOAT || type == OperandType::DOUBLE) {
				long double value = (long double)getData() * (long double)op->getData();
				return eval(value);
			} else {
				ssize_t value = (ssize_t)getData() * (ssize_t)op->getData();
				return eval(value);
			}
		};

		auto *op1 = dynamic_cast<const Operand<int8_t> *>(&rhs);
		if (op1) {
			return mul(op1);
		}
		auto *op2 = dynamic_cast<const Operand<int16_t> *>(&rhs);
		if (op2) {
			return mul(op2);
		}
		auto *op3 = dynamic_cast<const Operand<int32_t> *>(&rhs);
		if (op3) {
			return mul(op3);
		}
		auto *op4 = dynamic_cast<const Operand<float> *>(&rhs);
		if (op4) {
			return mul(op4);
		}
		auto *op5 = dynamic_cast<const Operand<double> *>(&rhs);
		if (op5) {
			return mul(op5);
		}
		throw AVMException(Reason::UNKNOWN_OPERAND, "Multiply of unknown operand");
	}

	IOperand const *operator/(IOperand const &rhs) const
	{
		auto div = [&](auto *op) -> IOperand const * {
			OperandType type = this->getPrecision() >= op->getPrecision() ? 
							   this->getType() : op->getType();

			auto eval = std::bind([&](OperandType type, auto value) { return runtimeEvaluationOf(type, value); },
								  type, std::placeholders::_1);


			if (op->getData() == 0) {
				throw AVMException(Reason::DIVISION_BY_ZERO, std::to_string(this->getData()) + " by " + std::to_string(op->getData()));
			}

			if (type == OperandType::FLOAT || type == OperandType::DOUBLE) {
				long double value = (long double)getData() / (long double)op->getData();
				return eval(value);
			} else {
				ssize_t value = (ssize_t)getData() / (ssize_t)op->getData();
				return eval(value);
			}
		};

		auto *op1 = dynamic_cast<const Operand<int8_t> *>(&rhs);
		if (op1) {
			return div(op1);
		}
		auto *op2 = dynamic_cast<const Operand<int16_t> *>(&rhs);
		if (op2) {
			return div(op2);
		}
		auto *op3 = dynamic_cast<const Operand<int32_t> *>(&rhs);
		if (op3) {
			return div(op3);
		}
		auto *op4 = dynamic_cast<const Operand<float> *>(&rhs);
		if (op4) {
			return div(op4);
		}
		auto *op5 = dynamic_cast<const Operand<double> *>(&rhs);
		if (op5) {
			return div(op5);
		}
		throw AVMException(Reason::UNKNOWN_OPERAND, "Multiply of unknown operand");
	}

	IOperand const *operator%(IOperand const &rhs) const
	{
		auto div = [&](auto *op) -> IOperand const * {
			OperandType type = this->getPrecision() >= op->getPrecision() ? 
							   this->getType() : op->getType();

			auto eval = std::bind([&](OperandType type, auto value) { return runtimeEvaluationOf(type, value); },
								  type, std::placeholders::_1);


			if (op->getData() == 0) {
				throw AVMException(Reason::MODULO_BY_ZERO, std::to_string(this->getData()) + " by " + std::to_string(op->getData()));
			}

			if (type == OperandType::FLOAT || type == OperandType::DOUBLE) {
				long double value = fmod((long double)getData(), (long double)op->getData());
				return eval(value);
			} else {
				ssize_t value = (ssize_t)getData() % (ssize_t)op->getData();
				return eval(value);
			}
		};

		auto *op1 = dynamic_cast<const Operand<int8_t> *>(&rhs);
		if (op1) {
			return div(op1);
		}
		auto *op2 = dynamic_cast<const Operand<int16_t> *>(&rhs);
		if (op2) {
			return div(op2);
		}
		auto *op3 = dynamic_cast<const Operand<int32_t> *>(&rhs);
		if (op3) {
			return div(op3);
		}
		auto *op4 = dynamic_cast<const Operand<float> *>(&rhs);
		if (op4) {
			return div(op4);
		}
		auto *op5 = dynamic_cast<const Operand<double> *>(&rhs);
		if (op5) {
			return div(op5);
		}
		throw AVMException(Reason::UNKNOWN_OPERAND, "Multiply of unknown operand");
	}

	IOperand const *square() const
	{
		OperandType type = (OperandType)getPrecision();

		auto square = std::bind([&](OperandType type, auto value) { return runtimeEvaluationOf(type, value); },
							  type, std::placeholders::_1);

		if (type == OperandType::FLOAT || type == OperandType::DOUBLE) {
			long double value = pow(getData(), 2.0);
			return square(value);
		} else {
			ssize_t value = pow(getData(), 2.0);
			return square(value);
		}
	}

	IOperand const *square_root() const
	{
		OperandType type = (OperandType)getPrecision();

		auto square_root = std::bind([&](OperandType type, auto value) { return runtimeEvaluationOf(type, value); },
							  type, std::placeholders::_1);

		if (type == OperandType::FLOAT || type == OperandType::DOUBLE) {
			long double value = sqrt(getData());
			return square_root(value);
		} else {
			ssize_t value = sqrt(getData());
			return square_root(value);
		}
	}

	IOperand const *nlog() const
	{
		OperandType type = (OperandType)getPrecision();

		auto nat_log = std::bind([&](OperandType type, auto value) { return runtimeEvaluationOf(type, value); },
							  type, std::placeholders::_1);

		if (type == OperandType::FLOAT || type == OperandType::DOUBLE) {
			long double value = log(getData());
			return nat_log(value);
		} else {
			ssize_t value = log(getData());
			return nat_log(value);
		}
	}

	IOperand const *log_10() const
	{
		OperandType type = (OperandType)getPrecision();

		auto mlog_10 = std::bind([&](OperandType type, auto value) { return runtimeEvaluationOf(type, value); },
							  type, std::placeholders::_1);

		if (type == OperandType::FLOAT || type == OperandType::DOUBLE) {
			long double value = log10(getData());
			return mlog_10(value);
		} else {
			ssize_t value = log10(getData());
			return mlog_10(value);
		}
	}

	IOperand const *absolute() const
	{
		OperandType type = (OperandType)getPrecision();

		auto mlog_10 = std::bind([&](OperandType type, auto value) { return runtimeEvaluationOf(type, value); },
							  type, std::placeholders::_1);

		if (type == OperandType::FLOAT || type == OperandType::DOUBLE) {
			long double value = abs(getData());
			return mlog_10(value);
		} else {
			ssize_t value = abs(getData());
			return mlog_10(value);
		}
	}

private:
	Operand() : IOperand() {};

	IOperand const *runtimeEvaluationOf(OperandType type, ssize_t value) const
	{
		switch (type)
		{
			case OperandType::INT8:
			{
				if (value > INT8_MAX)
					throw AVMException(Reason::OVERFLOW_INT8_ERROR, "Resulting value: " + std::to_string(value));
				if (value < INT8_MIN)
					throw AVMException(Reason::UNDERFLOW_INT8_ERROR, "Resulting value: " + std::to_string(value));
				return OperandFactory::createOperand<int8_t>(OperandType::INT8, value);
			}
			case OperandType::INT16:
			{
				if (value > INT16_MAX)
					throw AVMException(Reason::OVERFLOW_INT8_ERROR, "Resulting value: " + std::to_string(value));
				if (value < INT16_MIN)
					throw AVMException(Reason::UNDERFLOW_INT8_ERROR, "Resulting value: " + std::to_string(value));
				return OperandFactory::createOperand<int16_t>(OperandType::INT16, value);
			}
			case OperandType::INT32:
			{
				if (value > INT32_MAX)
					throw AVMException(Reason::OVERFLOW_INT32_ERROR, "Resulting value: " + std::to_string(value));
				if (value < INT32_MIN)
					throw AVMException(Reason::UNDERFLOW_INT32_ERROR, "Resulting value: " + std::to_string(value));
				return OperandFactory::createOperand<int32_t>(OperandType::INT32, value);
			}
			default: {
				throw AVMException(Reason::UNKNOWN_OPERAND, "Unknown decimal operand");
			}
		}
	}

	IOperand const *runtimeEvaluationOf(OperandType type, long double value) const
	{
		switch (type)
		{
			case OperandType::FLOAT:
			{
				if (value > FLT_MAX)
					throw AVMException(Reason::OVERFLOW_FLT_ERROR, "Resulting value: " + std::to_string(value));
				if (value < -FLT_MAX)
					throw AVMException(Reason::UNDERFLOW_FLT_ERROR, "Resulting value: " + std::to_string(value));
				return OperandFactory::createOperand<float>(OperandType::FLOAT, value);
			}
			case OperandType::DOUBLE:
			{
				if (value > DBL_MAX)
					throw AVMException(Reason::OVERFLOW_DBL_ERROR, "Resulting value: " + std::to_string(value));
				if (value < -DBL_MAX)
					throw AVMException(Reason::UNDERFLOW_DBL_ERROR, "Resulting value: " + std::to_string(value));
				return OperandFactory::createOperand<double>(OperandType::DOUBLE, value);
			}
			default: {
				throw AVMException(Reason::UNKNOWN_OPERAND, "Unknown floating point operand");
			}
		}
	}

private:
	T m_data;
	OperandType m_type;
	std::string m_str;
};
