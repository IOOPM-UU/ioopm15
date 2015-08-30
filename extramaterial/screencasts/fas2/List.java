/**
 * @author Tobias Wrigstad (tobias.wrigstad@it.uu.se)
 * @date 2013-10-04
 */
public class List {
    private Link first = null;
    // Link last  = null;

    public void prepend(Object element) {
        first = new Link(first, element);
    }

    public boolean contains(Object element) {
        if (first == null) return false;

        return first.contains(element);
    }

    public String toString() {
        // FIXME
        return "[" + ((this.first == null) ? "" : this.first.stringify()) + "]";
    }

    /**
     * @author Tobias Wrigstad (tobias.wrigstad@it.uu.se)
     * @date 2013-10-04
     */
    private class Link {
	public Link() {
	    this(null, null);
	}
	public Link(Link next, Object element) {
	    this.next = next;
	    this.element = element;
	}

	private Link next;
	private Object element;

	public boolean contains(Object element) {
	    if (element == this.element) return true;
	    if (this.next == null) return false;

	    return next.contains(element);
	}

	public String toString() {
	    // FIXME
	    return element.toString() + ((this.next == null) ? "" : ", ");
	}

	public String stringify() {
	    // FIXME
	    return toString() + ((this.next == null) ? "" : this.next.stringify());
	}
    }

}
