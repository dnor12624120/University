package com.company.Domain.Factor;

import com.company.Domain.Evaluable;
import com.company.Domain.Operator.LowPrecedenceBinaryOperator;
import com.company.Domain.Primary;
import com.company.Domain.Value.Value;

public class Factor2 implements Evaluable
{
    private Evaluable primary1;
    private Evaluable primary2;
    private LowPrecedenceBinaryOperator operator;

    public Factor2(Evaluable primary1, Evaluable primary2, LowPrecedenceBinaryOperator operator)
    {
        this.primary1 = primary1;
        this.primary2 = primary2;
        this.operator = operator;
    }

    @Override
    public Value evaluate()
    {
        return operator.operate(primary1.getValue(), primary2.getValue());
    }
}
