package Domain.Entities;

import java.io.Serializable;

public abstract class BaseEntity<ID> implements Serializable
{
    protected ID id;

    public ID getID() {
        return id;
    }

    public void setID(ID id) {
        this.id = id;
    }
}
