package com.company;

import com.company.Token.Token;

import java.util.ArrayList;

public class Scanner
{


    public ArrayList<Token> tokenizeCode(String code)
    {
        ArrayList<Token> tokens = new ArrayList<>();
        for(String word : code.split(" |((?<=;)|(?=;))|((?<=\\()|(?=\\())|((?<=\\))|(?=\\)))|((?<=\\\n)|(?=\\\n))"))
        {
            if(!isWhitespace(word))
            {
                try
                {
                    tokens.add(convertWordToToken(word));
                }
                catch (Exception e)
                {
                    System.out.println(e.getMessage());
                }
            }
        }
        return tokens;
    }

    private Token convertWordToToken(String word) throws Exception
    {
        switch(word) {
            case "int": {
                return new Token(TokenType.INTEGER_KEYWORD);
            }
            case "bool": {
                return new Token(TokenType.BOOLEAN_KEYWORD);
            }
            case "if": {
                return new Token(TokenType.IF_KEYWORD);
            }
            case "then": {
                return new Token(TokenType.THEN_KEYWORD);
            }
            case "else": {
                return new Token(TokenType.ELSE_KEYWORD);
            }
            case "print":
            {
                return new Token(TokenType.PRINT_KEYWORD);
            }
            case "=": {
                return new Token(TokenType.ASSIGNMENT_OPERATOR);
            }
            case "+": {
                return new Token(TokenType.ARITHMETIC_ADDITION_OPERATOR);
            }
            case "-": {
                return new Token(TokenType.ARITHMETIC_SUBTRACTION_OPERATOR);
            }
            case "*": {
                return new Token(TokenType.ARITHMETIC_MULTIPLICATION_OPERATOR);
            }
            case "/": {
                return new Token(TokenType.ARITHMETIC_DIVISION_OPERATOR);
            }
            case "&&": {
                return new Token(TokenType.LOGICAL_AND_OPERATOR);
            }
            case "||": {
                return new Token(TokenType.LOGICAL_OR_OPERATOR);
            }
            case "==": {
                return new Token(TokenType.RELATINOAL_EQUALITY_OPERATOR);
            }
            case "!=": {
                return new Token(TokenType.RELATIONAL_INEQUALITY_OPERATOR);
            }
            case "(": {
                return new Token(TokenType.OPEN_PARANTHESIS);
            }
            case ")": {
                return new Token(TokenType.CLOSED_PARANTHESIS);
            }
            case ";":
            {
                return new Token(TokenType.SEMICOLON);
            }
            default:
            {
                if(word.matches("true|false"))
                {
                    return new Token(TokenType.BOOLEAN_LITERAL, word);
                }
                if(word.matches("[0-9]{1,9}"))
                {
                    return new Token(TokenType.INTEGER_LITERAL, word);
                }
                if(word.matches("[a-zA-Z]*[0-9]*"))
                {
                    return new Token(TokenType.SYMBOL_IDENTIFIER, word);
                }
                throw new Exception();
            }
        }
    }

    private boolean isWhitespace(String word)
    {
        return word.equals(" ") || word.equals("\n") || word.equals("\t");
    }
}
