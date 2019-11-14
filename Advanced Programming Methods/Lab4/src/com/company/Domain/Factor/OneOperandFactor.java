package com.company.Domain;

import com.company.Domain.Value.Value;

public class Primary
{
    Value value;

    public Primary(Value value)
    {
        this.value = value;
    }

    public Value getValue() { return value; }
    public void setValue(Value value) { this.value = value; }
}
