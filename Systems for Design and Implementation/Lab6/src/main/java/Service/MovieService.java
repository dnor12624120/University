package Service;

import Domain.Entities.Movie;
import Domain.Validators.RepositoryException;
import Domain.Validators.ValidatorException;
import Repository.SortingRepository;
import Utility.Utility;
import Utility.Sort;
import Utility.SortCriteria;
import Utility.SortOrder;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import java.io.IOException;
import java.sql.SQLException;
import java.util.List;
import java.util.Set;
import java.util.function.Predicate;

public class MovieService
{
    private SortingRepository<Integer, Movie> movieRepository;

    public MovieService(SortingRepository<Integer, Movie> movieRepository)
    {
        this.movieRepository = movieRepository;
    }

    public void addMovie(Movie movie) throws RepositoryException, ValidatorException, IOException, ParserConfigurationException, TransformerException, SAXException, SQLException, NoSuchFieldException, IllegalAccessException {
        movieRepository.save(movie).ifPresent(c -> { throw new RepositoryException("Cannot add specified movie."); });
    }

    public void deleteMovie(int movieID) throws RepositoryException, IOException, ParserConfigurationException, TransformerException, SAXException, SQLException {
        movieRepository.delete(movieID).orElseThrow(() -> new RepositoryException("Cannot delete specified movie"));
    }

    public void updateMovie(Movie movie) throws RepositoryException, ValidatorException, IOException, ParserConfigurationException, TransformerException, SAXException, SQLException, NoSuchFieldException, IllegalAccessException {
        movieRepository.update(movie).orElseThrow(() -> new RepositoryException("Cannot update specified movie"));
    }

    public Set<Movie> getAllMovies() throws SQLException, NoSuchFieldException, IllegalAccessException {
        return Utility.iterableToSet(movieRepository.findAll());
    }

    public Set<Movie> filterMovies(Predicate<Movie> predicate) throws SQLException, NoSuchFieldException, IllegalAccessException { return Utility.iterableToSet(movieRepository.filter(predicate));}

    public Set<Movie> getMostRentedMovies(Set<Integer> filteredRentals) throws SQLException, NoSuchFieldException, IllegalAccessException {
        return filterMovies(movie -> filteredRentals.stream().anyMatch(x -> x.equals(movie.getID())));
    }

    public List<Movie> getMoviesSortedByGenre() throws SQLException, NoSuchFieldException, IllegalAccessException {
        return (List<Movie>) movieRepository.findAll(new Sort(new SortCriteria(SortOrder.ASCENDING, "genre")).and(new SortCriteria(SortOrder.DESCENDING, "name")));
    }
}
