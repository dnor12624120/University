package com.company.Domain.Operator;

import com.company.Domain.Value.BooleanValue;
import com.company.Domain.Value.Value;

public class LogicalAndOperator implements MediumPrecedenceBinaryOperator
{
    @Override
    public Value operate(Value value1, Value value2)
    {
        boolean rawValue1 = (Boolean)value1.getValue();
        boolean rawValue2 = (Boolean)value2.getValue();

        return new BooleanValue(rawValue1 && rawValue2);
    }
}
