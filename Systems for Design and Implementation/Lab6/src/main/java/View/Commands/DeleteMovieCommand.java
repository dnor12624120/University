package View.Commands;

import Domain.Validators.RepositoryException;
import Domain.Validators.ValidatorException;
import Service.MovieService;
import Utility.Utility;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import java.io.IOException;
import java.sql.SQLException;

public class DeleteMovieCommand extends MenuCommand
{
    private MovieService movieService;

    public DeleteMovieCommand(String description, String index, MovieService movieService)
    {
        super(description, index);
        this.movieService = movieService;
    }

    @Override
    public void execute()
    {
        int id = Utility.readNextIntFromConsole("Enter movie ID.");
        try
        {
            movieService.deleteMovie(id);
        }
        catch (ValidatorException | RepositoryException | IOException | TransformerException | SAXException | ParserConfigurationException | SQLException exception)
        {
            System.out.println(exception.getMessage());
        }
    }
}
