package View.Commands;

import Domain.Validators.ValidatorException;
import Service.MovieService;

import java.sql.SQLException;

public class ViewAllMoviesCommand extends MenuCommand
{
    private MovieService movieService;

    public ViewAllMoviesCommand(String description, String index, MovieService movieService)
    {
        super(description, index);
        this.movieService = movieService;
    }

    @Override
    public void execute()
    {
        try
        {
            movieService.getAllMovies().forEach(System.out::println);
        }
        catch (ValidatorException | SQLException | NoSuchFieldException | IllegalAccessException exception)
        {
            System.out.println(exception.getMessage());
        }
    }
}
