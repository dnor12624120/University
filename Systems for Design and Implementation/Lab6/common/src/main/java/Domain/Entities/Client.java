package Domain.Entities;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.Serializable;

public class Client extends BaseEntity<Integer> implements Serializable
{
    private String name;
    private int age;

    public Client()
    {
    }

    public Client(String name, int age)
    {
        this.name = name;
        this.age = age;
    }

    public String getName() {
        return name;
    }

    public int getAge() {
        return age;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setAge(int age) {
        this.age = age;
    }

    @Override
    public boolean equals(Object object)
    {
        if (this == object)
        {
            return true;
        }
        if (object == null || getClass() != object.getClass())
        {
            return false;
        }

        Client client = (Client) object;
        if (age != client.age)
        {
            return false;
        }
        return name.equals(client.name);

    }

    @Override
    public String toString()
    {
        return id + " " + name + " " + age;
    }
}
