package View.Commands;


import Domain.Entities.Movie;
import Domain.Validators.RepositoryException;
import Domain.Validators.ValidatorException;
import Service.MovieService;
import Service.RentalService;

import java.sql.SQLException;
import java.util.Set;
import java.util.concurrent.ExecutionException;

public class ViewMostRentedMoviesCommand extends MenuCommand
{
    private final MovieService movieService;

    public ViewMostRentedMoviesCommand(String description, String index, MovieService movieService)
    {
        super(description, index);
        this.movieService = movieService;
    }

    @Override
    public void execute()
    {
        try
        {
            Set<Movie> mostRentedMovies = movieService.getMostRentedMovies().get();
            mostRentedMovies.forEach(System.out::println);
        }
        catch (ValidatorException | RepositoryException | InterruptedException | ExecutionException exception)
        {
            System.out.println(exception.getMessage());
        }
    }
}
