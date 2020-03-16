package View;

import Domain.Movie;
import Domain.Validators.ValidatorException;
import Service.MovieService;
import Utility.Utility;

import java.util.Scanner;

public class AddMovieCommand extends MenuCommand
{
    private MovieService movieService;
    private Scanner inputStream;

    public AddMovieCommand(String description, String index, MovieService movieService)
    {
        super(description, index);
        this.movieService = movieService;
    }

    @Override
    public void execute()
    {
        int id = Utility.readNextIntFromConsole("Enter movie ID.");
        String name = Utility.readNextLineFromConsole("Enter movie title.");
        String genre = Utility.readNextLineFromConsole("Enter movie genre.");
        String description = Utility.readNextLineFromConsole("Enter movie description.");
        try
        {
            Movie movie = new Movie(name, genre, description);
            movie.setID(id);
            movieService.addMovie(movie);
        }
        catch (ValidatorException exception)
        {
            System.out.println(exception.getMessage());
        }
    }
}
