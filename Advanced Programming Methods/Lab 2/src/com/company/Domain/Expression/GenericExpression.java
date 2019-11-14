package com.company.Domain.Expression;

import com.company.Containers.Dictionary.DictionaryWrapper;
import com.company.Domain.Value.Value;
import com.company.Exceptions.DivisionByZeroException;

public interface Expression
{
    Value evaluate(DictionaryWrapper<String, Value> symbolTable) throws DivisionByZeroException;
}
