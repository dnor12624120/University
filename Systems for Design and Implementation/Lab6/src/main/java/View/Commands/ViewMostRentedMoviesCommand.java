package View.Commands;


import Domain.Entities.Movie;
import Domain.Validators.RepositoryException;
import Domain.Validators.ValidatorException;
import Service.MovieService;
import Service.RentalService;

import java.sql.SQLException;
import java.util.Set;

public class ViewMostRentedMoviesCommand extends MenuCommand
{
    private RentalService rentalService;
    private MovieService movieService;

    public ViewMostRentedMoviesCommand(String description, String index, RentalService rentalService, MovieService movieService)
    {
        super(description, index);
        this.rentalService = rentalService;
        this.movieService = movieService;
    }

    @Override
    public void execute()
    {
        try
        {
            int maxNumOfRentalsPerMovie = rentalService.getMaxNumOfRentalsPerMovie();
            Set<Integer> filteredRentals = rentalService.getMostRentedMovieIDs();
            Set<Movie> mostRentedMovies = movieService.getMostRentedMovies(filteredRentals);
            System.out.println("The following movie(s) have been rented " + maxNumOfRentalsPerMovie + " times.");
            mostRentedMovies.forEach(System.out::println);
        }
        catch (ValidatorException | RepositoryException | IllegalAccessException | SQLException | NoSuchFieldException exception)
        {
            System.out.println(exception.getMessage());
        }
    }
}
