namespace Domain.Repositories;

public class MovieSearchParams
{
    public int? Limit { get; set; }

    public int? Offset { get; set;} 

    public float? MinRating { get; set; }

    public bool? IsForeign { get; set; }
}
