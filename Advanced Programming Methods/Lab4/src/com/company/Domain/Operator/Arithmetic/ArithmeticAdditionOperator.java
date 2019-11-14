package com.company.Domain.Operator;

import com.company.Domain.Value.IntegerValue;
import com.company.Domain.Value.Value;

public class ArithmeticAdditionOperator implements LowPrecedenceBinaryOperator
{
    @Override
    public Value operate(Value value1, Value value2)
    {
        int rawValue1 = (Integer)value1.getValue();
        int rawValue2 = (Integer)value2.getValue();

        return new IntegerValue(rawValue1 + rawValue2);
    }
}
