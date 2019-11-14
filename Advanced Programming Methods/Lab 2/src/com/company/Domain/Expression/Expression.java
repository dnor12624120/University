package com.company.Domain.Expression;

import com.company.Containers.Dictionary.DictionaryWrapper;
import com.company.Domain.Operator.BinaryOperator;
import com.company.Domain.Value.IntegerValue;
import com.company.Domain.Value.Value;
import com.company.Exceptions.DivisionByZeroException;

public class ArithmeticExpression implements Expression
{
    private Expression expression1;
    private Expression expression2;
    private BinaryOperator operator;

    public ArithmeticExpression(Expression expression1, Expression expression2, BinaryOperator operator)
    {
        this.expression1 = expression1;
        this.expression2 = expression2;
        this.operator = operator;
    }

    public IntegerValue evaluate(DictionaryWrapper<String, Value> symbolTable) throws DivisionByZeroException
    {
        return (IntegerValue) operator.operate(expression1.evaluate(symbolTable), expression2.evaluate(symbolTable));
    }
}
