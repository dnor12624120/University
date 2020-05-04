package Domain.Entities;

import java.io.Serializable;

public class Rental extends BaseEntity<Integer> implements Serializable
{
    private int clientID;
    private int movieID;

    public Rental()
    {

    }

    public Rental(int clientID, int movieID)
    {
        this.clientID = clientID;
        this.movieID = movieID;
    }

    public int getClientID()
    {
        return clientID;
    }

    public int getMovieID()
    {
        return movieID;
    }

    @Override
    public boolean equals(Object object)
    {
        return this == object;
    }

    @Override
    public String toString()
    {
        return id + " " + clientID + " " + movieID;
    }
}
