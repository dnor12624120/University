package Domain.Entities;

import javafx.util.Pair;
import Utility.Utility;
import org.w3c.dom.Document;
import org.w3c.dom.Element;

import java.io.BufferedReader;
import java.io.IOException;
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
    public void readFromFile(BufferedReader reader) throws IOException
    {
        super.id = Integer.parseInt(reader.readLine());
        this.clientID = Integer.parseInt(reader.readLine());
        this.movieID = Integer.parseInt(reader.readLine());
    }

    @Override
    public String getEntityTag() {
        return "rental";
    }

    @Override
    public String toString()
    {
        return "Rental\n{" + "\t\nclientID=" + clientID  +
                ",\t\nmovieID=" + movieID  +
                ",\t\n" + super.toString() +
                "\n}";
    }

    @Override
    public void initializeFromXMLElement(Element element)
    {
        super.id = Integer.parseInt(Utility.getValueFromElement(Utility.getSoleElementWithAttribute(element, "id")));
        clientID = Integer.parseInt(Utility.getValueFromElement(Utility.getSoleElementWithAttribute(element, "client_id")));
        movieID = Integer.parseInt(Utility.getValueFromElement(Utility.getSoleElementWithAttribute(element, "movie_id")));
    }

    @Override
    public void appendXMLContentToDocument(Document document, Element root)
    {
        Element clientElement = document.createElement("rental");
        Utility.addAttributeToElement(document, clientElement, "id", super.id.toString());
        Utility.addAttributeToElement(document, clientElement, "client_id", Integer.toString(clientID));
        Utility.addAttributeToElement(document, clientElement, "movie_id", Integer.toString(movieID));
        root.appendChild(clientElement);
    }
}
