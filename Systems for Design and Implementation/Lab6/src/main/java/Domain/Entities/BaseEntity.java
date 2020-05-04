package Domain.Entities;

import Domain.PlainTextReadable;
import Domain.XMLReadable;

import java.io.Serializable;

public abstract class BaseEntity<ID> implements PlainTextReadable, XMLReadable, Serializable
{
    protected ID id;

    public ID getID() {
        return id;
    }

    public void setID(ID id) {
        this.id = id;
    }

    public abstract String getEntityTag();

    @Override
    public String toString()
    {
        return "BaseEntity\n{" +
                "\t\nid=" + id.toString() +
                "\n}";
    }


}
