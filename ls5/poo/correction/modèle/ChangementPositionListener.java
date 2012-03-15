package modèle;
import java.util.EventListener;

public interface ChangementPositionListener extends EventListener
{
	public void PositionChangée(ChangementPositionEvent event);
}
