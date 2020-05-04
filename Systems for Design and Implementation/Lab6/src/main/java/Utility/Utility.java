package Utility;

import Domain.Entities.BaseEntity;
import org.w3c.dom.Document;
import org.w3c.dom.Element;


import java.io.*;
import java.lang.reflect.Field;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.StreamSupport;

public class Utility
{
    public static <T> Set<T> iterableToSet(Iterable<T> iterable)
    {
        return StreamSupport.stream(iterable.spliterator(), false).collect(Collectors.toSet());
    }

    public static <T> List<T> iterableToList(Iterable<T> iterable)
    {
        return StreamSupport.stream(iterable.spliterator(), false).collect(Collectors.toList());
    }

    public static String readNextLineFromConsole(String prompt)
    {
        Scanner inputStream = new Scanner(System.in);
        System.out.println(prompt);
        return inputStream.nextLine();
    }

    public static int readNextIntFromConsole(String prompt)
    {
        Scanner inputStream = new Scanner(System.in);
        System.out.println(prompt);
        return inputStream.nextInt();
    }

    public static Element getSoleElementWithAttribute(Element element, String attribute)
    {
        return (Element)element.getElementsByTagName(attribute).item(0);
    }

    public static String getValueFromElement(Element element)
    {
        return element.getFirstChild().getTextContent();
    }

    public static void addAttributeToElement(Document document, Element parent, String tag, String content)
    {
        Element newElement = document.createElement(tag);
        newElement.appendChild(document.createTextNode(content));
        parent.appendChild(newElement);
    }

    public static boolean isFileEmpty(String filepath)
    {
        try
        {
            BufferedReader reader = new BufferedReader(new FileReader(filepath));
            if (reader.readLine() == null)
            {
                return true;
            }
        }
        catch (IOException ignored)
        {
            return false;
        }
        return false;
    }

    public static void clearContentsOfFile(String filepath) throws IOException
    {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filepath)))
        {
            writer.write("");
        }
    }

    public static void createBlankXMLTemplate(String filepath) throws IOException
    {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filepath)))
        {
            writer.write("<list>\n</list>");
        }
    }

    public static <ID> String getAllFieldsString(BaseEntity<ID> entity) throws NoSuchFieldException {
        ArrayList<Field> fields = new ArrayList<>(Arrays.asList(entity.getClass().getDeclaredFields()));
        fields.add(0, entity.getClass().getSuperclass().getDeclaredField("id"));
        return fields.stream().
               map(Field::getName).
               collect(Collectors.joining(","));
    }

    public static <ID> String getNonIDFieldsFormattedString(BaseEntity<ID> entity) throws NoSuchFieldException {
        ArrayList<Field> fields = new ArrayList<>(Arrays.asList(entity.getClass().getDeclaredFields()));
        return fields.stream().
                map(field -> field.getName() + "=?").
                collect(Collectors.joining(","));
    }

    public static <ID> String getFieldFormatString(BaseEntity<ID> entity)
    {
        return IntStream.rangeClosed(0, entity.getClass().getDeclaredFields().length).mapToObj(i -> "?").collect(Collectors.joining(","));
    }
}
