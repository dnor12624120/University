package View.Commands;

import Domain.Entities.Movie;
import Domain.Validators.RepositoryException;
import Domain.Validators.ValidatorException;
import Service.MovieService;
import Utility.Utility;

public class AddMovieCommand extends MenuCommand
{
    private final MovieService movieService;

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
        catch (RepositoryException | ValidatorException exception)
        {
            System.out.println(exception.getMessage());
        }
    }
}
