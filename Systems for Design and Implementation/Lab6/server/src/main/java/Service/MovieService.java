package Service;

import Domain.Entities.Movie;
import Domain.Validators.RepositoryException;
import Domain.Validators.ValidatorException;
import Repository.SortingRepository;
import Utility.Sort;
import Utility.SortCriteria;
import Utility.SortOrder;
import Utility.Utility;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import java.io.IOException;
import java.sql.SQLException;
import java.util.List;
import java.util.Set;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;
import java.util.function.Predicate;

public class MovieService
{
    private SortingRepository<Integer, Movie> movieRepository;
    ExecutorService executorService;

    public MovieService(SortingRepository<Integer, Movie> movieRepository, ExecutorService executorService)
    {
        this.movieRepository = movieRepository;
        this.executorService = executorService;
    }

    public Future<Boolean> addMovie(Movie movie) throws RepositoryException, ValidatorException
    {
        return executorService.submit(() -> !movieRepository.save(movie).isPresent());
    }

    public Future<Boolean> deleteMovie(int movieID) throws RepositoryException
    {
        return executorService.submit(() -> movieRepository.delete(movieID).isPresent());
    }

    public Future<Boolean> updateMovie(Movie movie) throws RepositoryException, ValidatorException
    {
        return executorService.submit(() -> movieRepository.update(movie).isPresent());
    }

    public Future<Set<Movie>> getAllMovies()
    {
        return executorService.submit(() -> Utility.iterableToSet(movieRepository.findAll()));
    }

    private Set<Movie> filterMovies(Predicate<Movie> predicate) throws SQLException, NoSuchFieldException, IllegalAccessException
    {
        return Utility.iterableToSet(movieRepository.filter(predicate));
    }

    public Future<Set<Movie>> getMostRentedMovies(Set<Integer> filteredRentals)
    {
        return executorService.submit(() -> filterMovies(movie -> filteredRentals.stream().anyMatch(x -> x.equals(movie.getID()))));
    }

    public Future<List<Movie>> getMoviesSortedByGenre()
    {
        return executorService.submit(() -> (List<Movie>) movieRepository.findAll(new Sort(new SortCriteria(SortOrder.ASCENDING, "genre")).and(new SortCriteria(SortOrder.DESCENDING, "name"))));
    }
}
