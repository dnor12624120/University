package Utility;

import Domain.Entities.BaseEntity;
import Domain.Entities.Client;
import Domain.Entities.Movie;
import Domain.Entities.Rental;
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

    public static Client stringToClient(String message)
    {
        String[] tokens = message.split(" ");
        Client client = new Client(tokens[1], Integer.parseInt(tokens[2]));
        client.setID(Integer.parseInt(tokens[0]));
        return client;
    }

    public static Movie stringToMovie(String message)
    {
        String[] tokens = message.split(" ");
        Movie movie = new Movie(tokens[1], tokens[2], tokens[3]);
        movie.setID(Integer.parseInt(tokens[0]));
        return movie;
    }

    public static Rental stringToRental(String message)
    {
        String[] tokens = message.split(" ");
        Rental rental = new Rental(Integer.parseInt(tokens[1]), Integer.parseInt(tokens[2]));
        rental.setID(Integer.parseInt(tokens[0]));
        return rental;
    }
}
