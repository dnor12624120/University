package Domain.Validators;

public class RepositoryException extends MovieRentalException
{
    public RepositoryException(String message)
    {
        super(message);
    }

    public RepositoryException(String message, Throwable cause)
    {
        super(message, cause);
    }

    public RepositoryException(Throwable cause)
    {
        super(cause);
    }

    public RepositoryException() { super(); }

}
