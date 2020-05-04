package View.Commands;

import Domain.Validators.RepositoryException;
import Domain.Validators.ValidatorException;
import Service.MovieService;

import java.sql.SQLException;


public class ViewMoviesSortedByGenreCommand extends MenuCommand
{
    private MovieService movieService;

    public ViewMoviesSortedByGenreCommand(String description, String index, MovieService movieService)
    {
        super(description, index);
        this.movieService = movieService;
    }

    @Override
    public void execute()
    {
        try
        {
            movieService.getMoviesSortedByGenre().forEach(System.out::println);
        }
        catch (ValidatorException | RepositoryException | SQLException exception)
        {
            System.out.println(exception.getMessage());
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (NoSuchFieldException e) {
            e.printStackTrace();
        }
    }
}
