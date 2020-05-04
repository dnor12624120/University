package Domain.Entities;

import org.w3c.dom.*;

import Utility.Utility;
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
    public void readFromFile(BufferedReader reader) throws IOException
    {
        super.id = Integer.parseInt(reader.readLine());
        this.name = reader.readLine();
        this.age = Integer.parseInt(reader.readLine());
    }

    @Override
    public String getEntityTag() {
        return "client";
    }

    @Override
    public String toString()
    {
        return "Client\n{" +
                "\t\nname='" + name + '\'' +
                ", \t\nage=" + age  + '\n' +
                super.toString() +
                "\n}";
    }

    @Override
    public void initializeFromXMLElement(Element element)
    {
        super.id = Integer.parseInt(Utility.getValueFromElement(Utility.getSoleElementWithAttribute(element, "id")));
        this.name = Utility.getValueFromElement(Utility.getSoleElementWithAttribute(element, "name"));
        this.age = Integer.parseInt(Utility.getValueFromElement(Utility.getSoleElementWithAttribute(element, "age")));
    }

    @Override
    public void appendXMLContentToDocument(Document document, Element root)
    {
        Element clientElement = document.createElement("client");
        Utility.addAttributeToElement(document, clientElement, "id", super.id.toString());
        Utility.addAttributeToElement(document, clientElement, "name", this.name);
        Utility.addAttributeToElement(document, clientElement, "age", Integer.toString(this.age));
        root.appendChild(clientElement);
    }
}
