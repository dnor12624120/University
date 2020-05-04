package Domain;

import Domain.Entities.Movie;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class MovieTest {

    @Test
    void getName() {
        String name = "name";
        String genre = "genre";
        String description = "description";
        Movie movie = new Movie(name, genre, description);
        assertEquals("name", movie.getName());
    }

    @Test
    void getGenre() {
        String name = "name";
        String genre = "genre";
        String description = "description";
        Movie movie = new Movie(name, genre, description);
        assertEquals("genre", movie.getGenre());
    }

    @Test
    void getDescription() {
        String name = "name";
        String genre = "genre";
        String description = "description";
        Movie movie = new Movie(name, genre, description);
        assertEquals("description", movie.getDescription());
    }

    @Test
    void setName() {
        Movie movie = new Movie("", "", "");
        movie.setName("name");
        assertEquals("name", movie.getName());
    }

    @Test
    void setGenre() {
        Movie movie = new Movie("", "", "");
        movie.setGenre("genre");
        assertEquals("genre", movie.getGenre());
    }

    @Test
    void setDescription() {
        Movie movie = new Movie("", "", "");
        movie.setDescription("description");
        assertEquals("description", movie.getDescription());
    }
}