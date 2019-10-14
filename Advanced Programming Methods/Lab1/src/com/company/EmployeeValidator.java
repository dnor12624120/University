package com.company;

public class EmployeeValidator
{
    public static void validateEmployee(Employee employee) throws EmployeeException {
        if(employee.getID() < 0)
        {
            throw new EmployeeException("Employee ID cannot be negative");
        }
    }
}
