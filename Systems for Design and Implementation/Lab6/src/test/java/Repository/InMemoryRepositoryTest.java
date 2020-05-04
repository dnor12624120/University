package Repository;

import Domain.Entities.Movie;
import Domain.Validators.GenericValidator;
import Utility.Utility;
import org.junit.jupiter.api.Test;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import java.io.IOException;
import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.*;

class InMemoryRepositoryTest {

    @Test
    void findOne() {
        InMemoryRepository<Integer, Movie> repository = new InMemoryRepository<Integer, Movie>(new GenericValidator<>(new ArrayList<>()));
        Movie movie = new Movie("name", "genre", "description");
        movie.setID(1);
        try
        {
            repository.save(movie);
        }
        catch (SAXException | TransformerException | ParserConfigurationException | IOException ignored)
        {
        }
        assertEquals(movie, repository.findOne(1).get());
    }

    @Test
    void findAll()
    {
        InMemoryRepository<Integer, Movie> repository = new InMemoryRepository<Integer, Movie>(new GenericValidator<>(new ArrayList<>()));
        Movie movie = new Movie("name", "genre", "description");
        movie.setID(1);
        try
        {
            repository.save(movie);
        }
        catch (SAXException | TransformerException | ParserConfigurationException | IOException ignored)
        {
        }
        assertEquals(1, Utility.iterableToList(repository.findAll()).size());
    }

    @Test
    void save()
    {
        InMemoryRepository<Integer, Movie> repository = new InMemoryRepository<Integer, Movie>(new GenericValidator<>(new ArrayList<>()));
        Movie movie = new Movie("name", "genre", "description");
        movie.setID(1);
        try
        {
            repository.save(movie);
        }
        catch (SAXException | TransformerException | ParserConfigurationException | IOException ignored)
        {
        }
        assertEquals(movie, repository.findOne(1).get());
    }

    @Test
    void delete() {
        InMemoryRepository<Integer, Movie> repository = new InMemoryRepository<Integer, Movie>(new GenericValidator<>(new ArrayList<>()));
        Movie movie = new Movie("name", "genre", "description");
        movie.setID(1);
        try
        {
            repository.save(movie);
            repository.delete(1);
        }
        catch (SAXException | TransformerException | ParserConfigurationException | IOException ignored)
        {
        }
        assertEquals(0, Utility.iterableToList(repository.findAll()).size());
    }
}